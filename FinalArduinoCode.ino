#include <math.h>

const int B = 4275000;
const int R0 = 100000;
const int pinTempSensor = A0;

const int MAX_SAMPLES = 120;  // Reduced from 240 to save memory
float tempData[MAX_SAMPLES];
float variationHistory[10];

int stableCycles = 0;
float totalVariation = 0.0;
float dominantFrequency = 0.0;
float samplingRate = 2.0;
int Number_of_Samples = 60;

const float variationThreshold = 0.5;
const float minSamplingRate = 0.5;
const float maxSamplingRate = 4.0;

#if defined(ARDUINO_ARCH_AVR)
  #define debug Serial
#elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_SAM)
  #define debug SerialUSB
#else
  #define debug Serial
#endif

void setup() {
  debug.begin(9600);
  debug.println(F("System Initialized"));
}

void loop() {
  Number_of_Samples = int(samplingRate * 60);
  if (Number_of_Samples > MAX_SAMPLES) Number_of_Samples = MAX_SAMPLES;

  debug.println(F("\nCollecting temperature data for 1 minute..."));
  collect_temperature_data();

  apply_dft();

  float predictedVariation = calculate_moving_average();
  int mode = decide_power_mode(predictedVariation);

  if (dominantFrequency > 0) {
    samplingRate = constrain(dominantFrequency * 2.0, minSamplingRate, maxSamplingRate);
  }

  debug.print(F("Predicted Variation: "));
  debug.print(predictedVariation, 2);
  debug.print(F(", Dominant Frequency: "));
  debug.print(dominantFrequency, 2);
  debug.print(F(" Hz, New Sampling Rate: "));
  debug.print(samplingRate, 2);
  debug.print(F(" Hz, Power Mode: "));
  switch (mode) {
    case 0: debug.println("ACTIVE"); break;
    case 1: debug.println("IDLE"); break;
    case 2: debug.println("POWER_DOWN"); break;
  }

  send_data_to_pc();
  delay(1000);
}

void collect_temperature_data() {
  totalVariation = 0.0;
  for (int i = 0; i < Number_of_Samples; i++) {
    int a = analogRead(pinTempSensor);
    if (a == 0) {
      tempData[i] = 0;
      continue;
    }
    float R = 1023.0 / a - 1.0;
    R = R0 * R;
    float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;
    tempData[i] = temperature;

    if (i > 0) {
      totalVariation += abs(temperature - tempData[i - 1]);
    }

    delay(int(1000 / samplingRate));
  }
}

void apply_dft() {
  dominantFrequency = 0.0;
  float maxMag = 0.0;

  for (int k = 1; k < Number_of_Samples / 2; k++) {
    float real = 0.0;
    float imag = 0.0;

    for (int n = 0; n < Number_of_Samples; n++) {
      float angle = 2.0 * PI * k * n / Number_of_Samples;
      real += tempData[n] * cos(angle);
      imag += tempData[n] * sin(angle);
    }

    float mag = sqrt(real * real + imag * imag);
    if (mag > maxMag) {
      maxMag = mag;
      dominantFrequency = (float)k / 60.0;  // 60 seconds window
    }
  }
}

float calculate_moving_average() {
  for (int i = 9; i > 0; i--) {
    variationHistory[i] = variationHistory[i - 1];
  }
  variationHistory[0] = totalVariation;

  float sum = 0.0;
  int count = 0;
  for (int i = 0; i < 10; i++) {
    if (variationHistory[i] > 0) {
      sum += variationHistory[i];
      count++;
    }
  }
  return (count > 0) ? (sum / count) : 0;
}

int decide_power_mode(float predictedVariation) {
  if (predictedVariation > variationThreshold) {
    stableCycles = 0;
    return 0; // ACTIVE
  } else if (stableCycles >= 5) {
    return 2; // POWER_DOWN
  } else {
    stableCycles++;
    return 1; // IDLE
  }
}

void send_data_to_pc() {
  debug.println(F("Time (s), Temperature (°C)"));
  for (int i = 0; i < Number_of_Samples; i++) {
    debug.print(i * (int)(1.0 / samplingRate));
    debug.print(", ");
    debug.println(tempData[i]);
  }
}

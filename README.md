# C-Coursework

Student ID: F427662

Solutions:

Task 1.1:

What is the reason for this issue?

This is because Google Colab only has access to public repositories, and because my repository was private it couldn't see it.

How does Google Colab access repositories?

Google colab access repositories using Github's API. It uses authentication when the user connects their colab account to their github account. 

What steps are needed to allow Google Colab to save notebooks to private repositories?

To allow google colab to save to private repositories. You have to sign in to google colab, save a file to github, and then sign into github. Grant permission for google colab to access private repositories.

How can you verify that your authentication settings are working correctly?

Go into your settings on github, then applications, then Authorised OAuth apps and find google colab. Click on it and check the scopes ensuring it says repo, which means it has full control of private repositories.

Task 1.3:

What does this message mean?

The message means that your are trying to delete a branch you are working on, and you can't delete it as it would make the codespace undefined.

Why does Git prevent this?

Git prevents this as if you delete the branch you are working on, as that would leave no active branch. It also prevents accidentally deleting your work.

How to properly delete a branch in Codespaces?

To delete a branch correctly, first switch to a different branch like the main and then run then delete the test branch by running, git branch -d test-branch.

Task 1.4:

What caused the merge conflict in this scenario?

The merge conflict occured because the same file was modified in two different ways, "Initial notes for the project." and "This is an update from main.". Git doesnt know what has more priority therefore an error occurs.

Why does Git prevent automatic merging when conflicts occur?

Git prevents automatic merging to avoid corruption. It doesn't want to assume which file has more priority as it could lead to data loss and corruption.

How can you prevent merge conflicts when working in a team environment?

Pull updates from the main branch frequently to stay up-to-date with main data changes. Avoid working on the same branch at one time with another team member. Smaller, frequent pushes allowing easier debugging. Communicate with team members on who is doing what tasks to prevent corruption and conflicts. 

What steps can you take to check for conflicts before merging changes?

Use git fetch and git merge origin/main into your feature branch locally to check conflicts before merging. Use git status to see what changes have been made to the main. You can use the function git rebase main in your feature branch to edit your branch and to resolve conflicts.

 What are the consequences of forcing a push without resolving a merge conflict?

It will corrupt the main branch data, and it be confusing to try and rectify errors. It could overwrite team members work and lead to data loss.

Task 3.1:
I created the function collect_temperature_data() which collects temperature for 3 minutes. I set the sampling rate of the temperature to 1Hz, so it reads the temperature every 1 second, which is that of the active mode. Inside the function, it reads the analog value of the tc thermistor and converts this to a voltage, which is then converts this to a temperature. I then also saved the 180 samples in a array.

Task 3.2:
I then introduced the function apply_dft(). In this function it carries out the DFT calculations. As arduino can't compute complex numbers, I had to calculate DFT using equation 3.4 and 3.5. The magnitudes from equation 3.5 are also stored for tasks 3.3

Task 3.3:
Then I created the function send_data_to_pc(), this function then sends the time-domain and frequency-domain data to the serial monitor. It is outputted in a csv format, in the order Time, Temperature, Frequency, and Magnitude.

Task 3.4:
For task 3.4, I created the function decide_power_mode(), in this function it detemines the power mode depending on the average frequency from the pervious DFT calculations. The power mode is determined and then outputted to the serial monitor.

Task 3.5:
After finishing Task 3.4, I opened Excel and enabled the Data Streamer add-in through COM Add-ins. After selecting the COM port connected to your Arduino, I renamed the table columns to Time, Temperature, Frequency, and Magnitude. I then started the data stream, allowed it to collect data for around three minutes, and saved the file as threeminstemperature_Student_ID.csv.

Task 3.6:
To create the python code to plot the time and frequency domain plots, I first imported the panda library to read the csv. Imported the csv file into google colab, so it could see it. Then wrote the code so it can read the csv and import the data from the csv. I then created the plots for both the time and frequency domain graphs. 

Task 4:
To optimize the sensor I first had to start using Dynamic Sampling, I made my number_of_samples variable dependent on the samplingrate. I limited Number_of_Samples to MAX_SAMPLES. I changed the 1000ms delay in the task 3.4 code depending on the samplingrate.
I added a totalvariation variable to track the temperature changes of consecutive values.I then created a function to calculate then moving average, this functions takes the recent changes in temperature and averages them out and gives an idea of the overall trend of the variation of temperature. I modified the decide_power_mode() to use the moving average and the variation threshold to determine the power states.
I then modified apply_dft() to find the the highest magnitude of frequency and store is as dominantFrequency.
Finally, I changed the loop to continously collect data after its finish 1 minute of data collection, and to also serial output updates of what the code is doing.




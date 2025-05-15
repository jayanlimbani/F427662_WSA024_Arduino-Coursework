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
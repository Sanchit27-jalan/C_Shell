# Description
This is a simple representation of the Bash shell coded in the C Programming language as a part of the Operating Systems and Networks course at IIIT-Hyderabad Monsoon 2023 semester. This branch is for the Mid-Submission of the project.It supports basic bash functionalities like cd , ls , history , piping , redirection , file management and networking.

# Various files 
header.h = Includes all the header files <br>
bg.c = It contains the code for execution of background process<br>
fg.c= it contains the code for execution of foreground process<br>
main.c= it contains the main code in which prompt is invoked and input is being taken<br>
pastevent.c=it contains the code for execution of pastevent<br>
peek.c=it contains the code for execution of peek <br>
processexec.c= It contains the code in which various processes are executed<br>
proclore.c=it contains the code for execution of proclore<br>
prompt.c=it contains the code for execution of prompt<br>
seek.c=it contains the code for execution of seek<br>
warp.c=It has the code for execution of warp .<br>
activity.c = It contains the code for execution of activities <br>
fg_to_bg.c = It contains the code for fg and bg execution (Specification 14)<br>
iman.c= It contains the code for execution of iMan command <br>
neonate.c = It contains the code for execution of Neonate Command <br>
pipe.c= It contains the code for execution of Piping <br>
signal.c = It contains the code for execution of Signals and Ctrl + C , Ctrl + D and Ctrl + Z . <br>

All .h files are used for linking stuff and defining <br>

# How to Run
Go to directory in which you save the file <br>
Run make in terminal <br>
Then run ./a.out<br>
# Assumptions
Assumed that bash-oriented commands and shell specific commands won't be given as a single multi-command thread<br>
Since the shell is under construction , it may throw some bugs at the user but that's what I'll be doing!Fixing them.<br>
Excessive care has been taken to handle all sorts of edge-cases but any if any such ambiguity still remains .<br>
In terminal if background process ends it ended part prints immediately but in our shell it prints before new prompt comes . <br>
Pastevent.txt contains some junk characters but in the code it does not effect.<br>
Proclore gives exact virtual memory .<br>
In some commands error handling hasn't been done but it will be in future.<br>
pastevent.txt file should already exist <br>
If sleep 5 or any command is working in background dont try to implement any execvp command in foreground .<br>
seek assumes that you dont pass extensions as file to be found and also assumes that you care about extensions of the file<br>
Specifications 1-6 and 8-11 and 16 were implemented on MACOS so they might give malloc errors elsewhere (when try to run them on Ubuntu)<br>
Specifications 7 and 12-15 were done on Parallels (Ubuntu) so they give best results on Ubuntu <br>
A control + \ keyboard interrupt is added to kill shell immediately <br>
In piping assumption has been made that command before 1st pipe would only contain input redirection and last command would contain output redirection. <br>



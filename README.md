## 1. To run the shell :
	make
	./a.out

## Built-in Commands:
2. 	echo : printing in the command line
	pwd : absolute path of the current directory
	cd : change the current directory
		cd .. -> changes to the previous directory
		cd . -> directory remains same
		cd <path> -> will change to that path
		cd ~ -> will bring you to the home directory
## Other Commands

3. ls : list directory contents(flags which can be given -l,-a,-la,-al,-a -l)

4. Foreground Process and Background Processes (ending with "&") 

5. pinfo : Gives Pid,status,Virtual Memeory and Executable path of the given process

6. clock : clock -t <interval> -n <duration> will display the date and time after specific intervals

7. reminder : remindme <time interval> <label> 

8. Semi-colon separated commands have been implemented

9. Overkill : kills all the background process

10. fg : puts the current background process in foreground

11. bg : puts the current stopped background process into running background process

12. jobs : prints all the current background jobs

13. kjob : kjob <job no> signal . performs a particular action on that job

14. setenv : sets the environment variable to particular value

15. unsetenv var : unsets that environment variable

16. quit : Shell quits

17. All piping commands,redirection and piping with redirection works


## FILES :

1. main.c : The main loop of the program.

2. compare.c : When user gives an input it calls the function accordingly.

3. function.c : Contains function for pwd and pinfo.

4. ls.c : executes ls command.

5. read.c : reads the user input and parses the command.

6. prompt.c : Displays the prompt,executes the cd command and gets a particular directory(for the ls command).

7. bg_fg.c : For running background and foreground process and a function will print the exit condition when background process has ended.

8. piping.c : For running all piped commands and running piped commands with redirection.

9. redir.c : For running input and output redirection 

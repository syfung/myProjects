This project based on the instruction that I took from a friend from University of Toronto CSC209. The idea is to implement a shell. For now it will be called miniShell or myShell. The starter code provides code for the prompting and tokenize the command.

At the moment, there is the '|' and  ';' operator, to chain command. Builtin command cd and exit. Also it is possible to run command by execvp, which will search the search path.

I am also working on adding the '&', '&&' and '||' operator.

Other optional feature that might be added includes printing the exit value of main, environment verable and the '*' things (wield cat).

Current State: 
	The shell does not exit properly after a command failliur. 
	Still trying to get 'emacs &' to work.

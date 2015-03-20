#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <mcheck.h>

#include "parser.h"
#include "shell.h"

/**
 * Program that simulates a simple shell.
 * The shell covers basic commands, including builtin commands 
 * (cd and exit only), standard I/O redirection and piping (|). 
 */

#define MAX_DIRNAME 100
#define MAX_COMMAND 1024
#define MAX_TOKEN 128

int execute_cd(char** words);
int execute_nonbuiltin(simple_command *s);
int execute_simple_command(simple_command *cmd);
int execute_complex_command(command *cmd);
int chained_pipe_command(command *cmd);
int chained_sequence_command(command *cmd);
int chained_parallel_command(command *cmd);
int chained_and_command(command *cmd);
int chained_or_command(command *cmd);


int main(int argc, char** argv) {
	
  char cwd[MAX_DIRNAME];           /* Current working directory */
  char command_line[MAX_COMMAND];  /* The command */
  char *tokens[MAX_TOKEN];         /* Command tokens (program name, 
				    * parameters, pipe, etc.) */

  while (1) {

    /* Display prompt */		
    getcwd(cwd, MAX_DIRNAME-1);
    printf("%s> ", cwd);
		
    /* Read the command line */
    fgets(command_line, MAX_COMMAND, stdin);
    /* Strip the new line character */
    if (command_line[strlen(command_line) - 1] == '\n') {

      command_line[strlen(command_line) - 1] = '\0';
    }
		
    /* Parse the command into tokens */
    parse_line(command_line, tokens);

    /* Check for empty command */
    if (!(*tokens)) {
      printf("Continue\n");
      continue;
    }
		
    /* Construct chain of commands, if multiple commands */
    command *cmd = construct_command(tokens);
    printf("Done command construct\n");
    print_command(cmd, 0);
    
    int exitcode = 0;
    if (cmd->scmd) {
      exitcode = execute_simple_command(cmd->scmd);
      printf("exitcode %d\n", exitcode);
      if (exitcode == -1) {
	break;
      }
    }
    else {
      exitcode = execute_complex_command(cmd);
      if (exitcode == -1) {
	break;
      }
    }
    release_command(cmd);
  }
  printf("Exiting\n");
  return 0;
}


/**
 * Changes directory to a path specified in the words argument;
 * For example: words[0] = "cd"
 *              words[1] = "csc209/assignment3/"
 * Your command should handle both relative paths to the current 
 * working directory, and absolute paths relative to root,
 * e.g., relative path:  cd csc209/assignment3/
 *       absolute path:  cd /u/bogdan/csc209/assignment3/
 */
int execute_cd(char** words) {
  
  if (words == NULL || words[0] == NULL ||\
      words[1] == NULL || strcmp(words[0],"cd")) {
    printf("EXIT_FAILURE: %d\n",EXIT_FAILURE);
    return EXIT_FAILURE;
  }

  if (is_relative(words[1])) {
    printf("Changing directry with relative path\n");
    char cwd[MAX_DIRNAME];
    getcwd(cwd,MAX_DIRNAME-1);
    strcat(cwd,"/");
    strcat(cwd,words[1]);
    printf("%s\n", cwd);
    return chdir(cwd);
  }
  else {
    printf("Changing directry with absolute path\n");
    return chdir(words[1]);
  }
	 
}


/**
 * Executes a program, based on the tokens provided as 
 * an argument.
 * For example, "ls -l" is represented in the tokens array by 
 * 2 strings "ls" and "-l", followed by a NULL token.
 * The command "ls -l | wc -l" will contain 5 tokens, 
 * followed by a NULL token. 
 */
int execute_command(char **tokens) {
	
  /* The exec program should exit itself */
  if (execvp(tokens[0],tokens) == -1) {
    fprintf(stderr,"Command no find: ");
    perror(tokens[0]);
    return EXIT_FAILURE;
  }
}


/**
 * Executes a non-builtin command.
 */
int execute_nonbuiltin(simple_command *s) {
  
  printf("Execute_nonbuiltin\n");

  /* Redirecting stdin */
  if (s->in != NULL) {
    printf("Redirecting stdin\n");
    int file_des_in = open(s->in, O_RDONLY);
    dup2(file_des_in, fileno(stdin));
    close(file_des_in);
  }

  /* Redirecting stdout */
  if (s->out != NULL) {
    printf("Redirecting stdout\n");
    int file_des_out = open(s->out, O_WRONLY | O_CREAT | O_TRUNC,\
			    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    dup2(file_des_out, fileno(stdout));
    close(file_des_out);
  }

  /* Redirecting stderr */
  if (s->err != NULL) {
    printf("Redirecting stderr\n");
    int file_des_err = open(s->err, O_WRONLY | O_CREAT | O_TRUNC,\
			    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    dup2(file_des_err, fileno(stderr));
    close(file_des_err);
  }

  /* Execeuting the command, only return if failed */  
  return execute_command(s->tokens);

}


/**
 * Executes a simple command (no pipes).
 */
int execute_simple_command(simple_command *cmd) {

  /* Check if it is a builtin command */
  switch (cmd->builtin) {
  case BUILTIN_CD:
    printf("case cd\n");
    return execute_cd(cmd->tokens);
  case BUILTIN_EXIT:
    printf("case exit\n");
    exit(0);
  }

  /* Forking a child process to execute the nonbuiltin command, the function should exit the child */ 
  int pid, status;
  if ((pid = fork()) == 0) {
    
    printf("Simple child\n");
    
    return execute_nonbuiltin(cmd);
  }
  else if (pid > 0) {
    waitpid(pid,&status,0);
    
    printf("Simple parent, done waiting child\n");
    printf("pid: %d, exit status: %d\n", pid,WEXITSTATUS(status));
 
  }
  else {    
    perror("fork, simple_command()");    
    exit(1);
  }

  return 0;
  
}


/**
 * Executes a complex command.  A complex command is two commands chained 
 * together with a pipe operator.
 */
int execute_complex_command(command *c) {

  if (c->scmd) {
    printf("Executing nonbuilting in complex command\n");
    return execute_nonbuiltin(c->scmd);
  }
  
  if (!c) {
    exit(0);
  }

  if (!strcmp(c->oper, "|")) {
    chained_pipe_command(c);
  }
  else if (!strcmp(c->oper, ";")) {
    chained_sequence_command(c);
  }
  else if (!strcmp(c->oper, "&")) {
    chained_parallel_command(c);
  }
  else if (!strcmp(c->oper, "&&")) {
    chained_and_command(c);
  }
  else if (!strcmp(c->oper, "||")) {
    chained_or_command(c);
  }
  return 0;
}


int chained_pipe_command(command *c) {

  int pipe_fd[2], pid;

  if (pipe(pipe_fd) != 0) {
    perror("pipe execute_complex_command()");
    return -1;
  }
  if (c->cmd1 == NULL || c->cmd2 == NULL) {
    printf("Piping to nowhere\n");
    return -1;
  }
  
  int comStatus, pid2, status2;


  if ((pid = fork()) == 0) {
    /* Linking the pipe as stdout */
    close(pipe_fd[0]);
    close(stdout);
    dup2(pipe_fd[1],fileno(stdout));

    execute_complex_command(c->cmd1);
    printf("This shouldn't do anything\n");
    exit(0);
  }
  else if (pid > 0) {
      
    waitpid(pid,&comStatus,0);
	
    if ((pid2 = fork()) == 0) {
      /* Linking// the pipe as stdin */
      close(pipe_fd[1]);
      close(stdin);
      dup2(pipe_fd[0],fileno(stdin));

      printf("Done waiting: %d ", pid);
      printf("Exit status of cmd1: %d\n", WEXITSTATUS(comStatus));

      execute_complex_command(c->cmd2);
      close(pipe_fd[0]);

      /* Exiting the extra parent */
      exit(0);
    }  
    else if (pid2 > 0) {
      close(pipe_fd[0]);
      close(pipe_fd[1]);

      waitpid(pid2,&status2,0);
	
      printf("Done waiting: %d\n", pid2);
      printf("pid: %d, exit status: %d\n", pid2,WEXITSTATUS(status2));
    }
    else {
      perror("fork, sequemce_command");
      exit(1);
    }
  }
  else {
    perror("fork, simple_command()");
    exit(1);
  }
  return 0;
}


int chained_sequence_command(command *cmd) {
  int pid, pid2, status1, status2;

  if ((pid = fork()) == 0) {
    execute_complex_command(cmd->cmd1);
  }
  else if (pid > 0) {
    waitpid(pid, status1, 0);
    if ((pid2 = fork()) == 0) {
      execute_complex_command(cmd->cmd2);
      exit(0);
    }
    else if (pid2 > 0) {
      waitpid(pid2, status2, 0);
      printf("Sequence command parent done wating\n");
    }
    else {
      perror("fork, sequemce_command");
      exit(1);
    }
  }
  else {
    perror("fork, sequemce_command");
    exit(1);
  }
  return 0;
}

int chained_parallel_command(command *cmd) {
  int pid, pid2, status1, status2;

  if ((pid = fork()) == 0) {
    execute_complex_command(cmd->cmd1);
  }
  else if (pid > 0) {
    if ((pid2 = fork()) == 0) {
      execute_complex_command(cmd->cmd2);    
    }
    else if (pid2 > 0) {  
      waitpid(pid, status1, WNOHANG);
      waitpid(pid2, status2, 0);
      printf("Sequence command parent done wating\n");
    }
    else {
      perror("fork, sequemce_command");
      exit(1);
    }
  }
  else {
    perror("fork, sequemce_command");
    exit(1);
  }
  return 0;
}

int chained_and_command(command *cmd) {
}
int chained_or_command(command *cmd) {
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include "shell.h"

int find_redirectInput(char ** args){
  int index = 0;
  const char *outDir = "<";
  while (args[index] != NULL) {
    if (strcmp(args[index], outDir) == 0) {
      return index;
    }
    index++;
  }
  return -1;
}

int find_redirectOutput(char ** args){
  int index = 0;
  const char *outDir = ">";
  while (args[index] != NULL) {
    if (strcmp(args[index], outDir) == 0) {
      return index;
    }
    index++;
  }
  return -1;
}

int find_pipe(char ** args){
  int index = 0;
  const char *outDir = "|";
  while (args[index] != NULL) {
    if (strcmp(args[index], outDir) == 0) {
      return index;
    }
    index++;
  }
  return -1;
}

int find_redirectAppend(char ** args){
  int index = 0;
  const char *outDir = ">>";
  while (args[index] != NULL) {
    if (strcmp(args[index], outDir) == 0) {
      return index;
    }
    index++;
  }
  return -1;
}

void redirectInput(int j, char ** command){
  char dest[100] = "";
  for (int i = 0; command[i] != NULL; i++) {
		strcat(dest, command[i]);
		strcat(dest, " ");
	}

  char ** commands = parse_args(dest, "<");

  int i = 0;
  while(commands[i] != NULL){
    if (commands[i][0] == 32) {
		    commands[i]++;
    }
	  if (commands[i][strlen(commands[i]) - 1] == 32) {
		    commands[i][strlen(commands[i]) - 1] = 0;
    }
    i++;
	}

	char ** toRun = parse_args(commands[0] , " ");
	int file = open(commands[1], O_RDONLY);

	if (fork() == 0) {
		dup2(file, STDIN_FILENO);
    execvp(toRun[0], toRun);
    exit(1);
	}

	close(file);
  wait(&j);
}


void redirectOutput(int j, char ** command){
  int delim = find_redirectOutput(command);
  char ** toRun = calloc(sizeof(char *), 10);
  int index = 0;
  while (index < delim){
    toRun[index] = command[index];
    index++;
  }

  int out = open(command[delim + 1], O_RDWR|O_CREAT|O_TRUNC, 0755);
  int d = dup(STDOUT_FILENO);
  if (fork() == 0) {
    dup2(out, 1);
    close(out);
    close(d);
    execvp(toRun[0], toRun);
    exit(1);
  }
  wait(&j);
}

void redirectDouble(int j, char ** command){
  int delim = find_redirectOutput(command);
  char * toWrite = command[delim + 1];
  char ** args;
  int index = 0;
  char dest[100] = "";
  for (int i = 0; i<delim; i++) {
		strcat(dest, command[i]);
		strcat(dest, " ");
	}

  char ** commands = parse_args(dest, "<");

  int i = 0;
  while(commands[i] != NULL){
    if (commands[i][0] == 32) {
		    commands[i]++;
    }
	  if (commands[i][strlen(commands[i]) - 1] == 32) {
		    commands[i][strlen(commands[i]) - 1] = 0;
    }
    i++;
	}
  char ** toRun = parse_args(commands[0] , " ");
  int rfile = open(commands[1], O_RDONLY);
  int wfile = open(toWrite, O_RDWR|O_CREAT|O_TRUNC, 0755);
  if (fork() == 0) {
		dup2(rfile, STDIN_FILENO);
		dup2(wfile, STDOUT_FILENO);
		execvp(toRun[0], toRun);
	  exit(1);
	}
  wait(&j);
  close(rfile);
  close(wfile);
}

void pipeCommand(int j, char ** command){
  char line[100] = "";
  for (int i = 0; command[i] != NULL; i++) {
		strcat(line, command[i]);
		strcat(line, " ");
	}
  line[strlen(line)-1] = 0;
  char ** commands = parse_args(line, "|");
  int i = 0;
  while(commands[i] != NULL){
    if (commands[i][0] == 32) {
		    commands[i]++;
    }
	  if (commands[i][strlen(commands[i]) - 1] == 32) {
		    commands[i][strlen(commands[i]) - 1] = 0;
    }
    i++;
	}
  char ** command1 = parse_args(commands[0], " ");
  char ** command2 = parse_args(commands[1], " ");

  int pippy[2];
  pipe(pippy);

  if (fork() == 0) {
    dup2(pippy[1], STDOUT_FILENO);
    execvp(command1[0], command1);
    exit(1);
  }
  wait(&j);

  if (fork() == 0) {
		dup2(pippy[0], STDIN_FILENO);
		close(pippy[1]);
		execvp(command2[0], command2);
		exit(1);
	}
  close(pippy[0]);
  close(pippy[1]);
  wait(&j);
}


void redirectAppend(int j, char ** command){
  int delim = find_redirectAppend(command);
  char ** toRun = calloc(sizeof(char *), 10);
  int index = 0;
  while (index < delim){
    toRun[index] = command[index];
    index++;
  }

  int out = open(command[delim + 1], O_RDWR|O_CREAT|O_APPEND, 0755);
  int d = dup(STDOUT_FILENO);
  if (fork() == 0) {
    dup2(out, 1);
    close(out);
    close(d);
    execvp(toRun[0], toRun);
    exit(1);
  }
  wait(&j);
}



//Given a string and a delimeter, parse_args seperates the string based on the
//given delimeter and returns an array of strings
char ** parse_args( char * line, char * delimeter){
  char *current = line;
  char *token;
  char ** args = malloc(10 * sizeof(char*));
  int i = 0;
  while(current != NULL){
    args[i] = strsep(&current, delimeter);
    if (i > 0 && strcmp(";", delimeter) == 0) {
      args[i]++;
    }
    i++;
  }
  args[i] = NULL;
  return args;
}

//Given two integers and a command seperated by spaces, runCommand executes the command through
//parsing and execvp
void runCommand(int j, int k, char input[]){
  input[strlen(input)-1] = 0;
  char * line = input;
  char ** args = parse_args(line, " ");
  if (find_redirectOutput(args) > -1 && find_redirectInput(args) > -1){
    redirectDouble(j, args);
  }
  else if (find_redirectOutput(args) > -1){
    redirectOutput(j, args);
  }
  else if (find_redirectInput(args) > -1){
    redirectInput(j, args);
  }
  else if (find_pipe(args) > -1) {
    pipeCommand(j, args);
	}
  else if (find_redirectAppend(args) > -1) {
    redirectAppend(j, args);
	}
  else{
    if (strcmp(args[0], "exit") == 0) {
      exit(0);
    }
    if (strcmp(args[0],  "cd" ) == 0) {
      chdir(args[1]);
    }
    k = fork();
    if(k==0) {
      //execvp(args[0], args);
      if (execvp(args[0], args) == -1)
						 exit(-1);
    }
    wait(&j);
  }
}

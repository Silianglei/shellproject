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
#include "headers.h"


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

void redirectOutput(char ** command){
  int delim = find_redirectOutput(command);
  char ** toRun = calloc(sizeof(char *), 10);
  int index = 0;
  while (index < delim){
    toRun[index] = command[index];
    index++;
  }

  int out = open(command[delim + 1], O_RDWR|O_CREAT|O_TRUNC);
  int d = dup(STDOUT_FILENO);
  if (fork() == 0) {
    dup2(out, 1);
    close(out);
    close(d);
    execvp(toRun[0], toRun);
  }
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
  if (find_redirectOutput(args) > -1){
    redirectOutput(args);
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
      execvp(args[0], args);
    }
    wait(&j);
  }
}

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


char ** parse_args( char * line ){
  char *current = line;
  char *token;
  char ** args = malloc(10 * sizeof(char*));
  int i = 0;
  while(current != NULL){
    args[i] = strsep(&current, " ");
    i++;
  }
  args[i] = NULL;
  return args;
}

void runCommand2(int j, int k, char input[]){
  input[strlen(input)-1] = 0;
  char * line = input;
  char ** args = parse_args( line );
  k = fork();
  if(k==0) {
    execvp(args[0], args);
  }
  wait(&j);
}

void runCommand(int j, int k){
  char input[100];
  fgets(input, sizeof(input), stdin);
  runCommand2(j, k, input);
  // input[strlen(input)-1] = 0;
  // char * line = input;
  // char ** args = parse_args( line );
  // k = fork();
  // if(k==0) {
  //   execvp(args[0], args);
  // }
  // wait(&j);
}



char ** parse_lines( char * lines ){
  char *current = lines;
  char *token;
  char ** args = malloc(10 * sizeof(char*));
  int i = 0;
  while(current != NULL){
    args[i] = strsep(&current, ";");\
    if (i > 0) {
      args[i]++;
    }
    i++;
  }
  args[i] = NULL;
  return args;
}

void runMult(int j, int k){
  char input[100];
  fgets(input, sizeof(input), stdin);
  char ** commandsToRun = parse_lines(input);
  int i = 0;
  while(commandsToRun[i] != NULL){
    //printf("'%s'\n", commandsToRun[i]);
    runCommand2(j, k, commandsToRun[i]);
    i++;
  }
}



int main(){
  int j;
  int k;
  while(1==1){
    printf("Input Your Command:");
    // char input[100];
    // fgets(input, sizeof(input), stdin);
    // input[strlen(input)-1] = 0;
    // char * line = input;
    // //printf("%s\n", line );
    // char ** args = parse_args( line );
    // k = fork();
    // if(k==0) {
    //   execvp(args[0], args);
    // }
    // wait(&j);
    char token[100] = "ls -a -l";
    runMult(j,k);
  }
  return 0;
}

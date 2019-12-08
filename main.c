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

//Given two integers and a command seperated by spaces, runCommand2 executes the command through
//parsing and execvp
void runCommand2(int j, int k, char input[]){
  input[strlen(input)-1] = 0;
  char * line = input;
  char ** args = parse_args(line, " ");
  if (strcmp(args[0], "exit") == 0) {
    return exit(0);
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

//Continously recieves user input
int main(int argc, char * argv[]){
  int j;
  int k;
  while(1){
    printf("Input Your Command:");
    char input[100];
    fgets(input, sizeof(input), stdin);
    char ** commandsToRun = parse_args(input, ";");
    int i = 0;
    while(commandsToRun[i] != NULL){
      //printf("'%s'\n", commandsToRun[i]);
      runCommand2(j, k, commandsToRun[i]);
      i++;
    }
  }
  return 0;
}

//Given two integers, runCommand gets user input and executes runCommand2.
// void runCommand(int j, int k){
//   char input[100];
//   fgets(input, sizeof(input), stdin);
//   runCommand2(j, k, input);
  // input[strlen(input)-1] = 0;
  // char * line = input;
  // char ** args = parse_args( line );
  // k = fork();
  // if(k==0) {
  //   execvp(args[0], args);
  // }
  // wait(&j);
// }


// // Given two integers, runMult recieves an array of commands, and executes
// //each of those commands.
// void runMult(int j, int k){
//   char input[100];
//   fgets(input, sizeof(input), stdin);
//   char ** commandsToRun = parse_args(input, ";");
//   int i = 0;
//   while(commandsToRun[i] != NULL){
//     //printf("'%s'\n", commandsToRun[i]);
//     runCommand2(j, k, commandsToRun[i]);
//     i++;
//   }
// }
// char ** parse_lines( char * lines ){
//   char *current = lines;
//   char *token;
//   char ** args = malloc(10 * sizeof(char*));
//   int i = 0;
//   while(current != NULL){
//     args[i] = strsep(&current, ";");\
//     if (i > 0) {
//       args[i]++;
//     }
//     i++;
//   }
//   args[i] = NULL;
//   return args;
// }

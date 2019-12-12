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
#include "functions.c"


//Continously recieves user input
int main(int argc, char * argv[]){
  int j;
  int k;
  char m[100];
  while(1){
    printf("%s# ", getcwd(m, 100));
    char input[100];
    fgets(input, sizeof(input), stdin);
    char ** commandsToRun = parse_args(input, ";");
    int i = 0;
    while(commandsToRun[i] != NULL){
      //printf("'%s'\n", commandsToRun[i]);
      runCommand(j, k, commandsToRun[i]);
      i++;
    }
  }
  return 0;
}



//Given a string and a delimeter, parse_args seperates the string based on the
//given delimeter and returns an array of strings
// char ** parse_args( char * line, char * delimeter){
//   char *current = line;
//   char *token;
//   char ** args = malloc(10 * sizeof(char*));
//   int i = 0;
//   while(current != NULL){
//     args[i] = strsep(&current, delimeter);
//     if (i > 0 && strcmp(";", delimeter) == 0) {
//       args[i]++;
//     }
//     i++;
//   }
//   args[i] = NULL;
//   return args;
// }
//
// //Given two integers and a command seperated by spaces, runCommand executes the command through
// //parsing and execvp
// void runCommand(int j, int k, char input[]){
//   input[strlen(input)-1] = 0;
//   char * line = input;
//   char ** args = parse_args(line, " ");
//   if (strcmp(args[0], "exit") == 0) {
//     exit(0);
//   }
//   if (strcmp(args[0],  "cd" ) == 0) {
//     chdir(args[1]);
//   }
//   k = fork();
//   if(k==0) {
//     execvp(args[0], args);
//   }
//   wait(&j);
// }

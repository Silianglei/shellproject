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


//Continously recieves user input
int main(){
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

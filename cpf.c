#include "stdio.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#define readsize 2

int main(int argc, char const *argv[]) {
  if(argc != 3){
    printf("Note three arguments given\n" );
    return 0;
  }
  int secondfile = open(argv[2],O_WRONLY);
  if(secondfile < 0){
    secondfile = creat(argv[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    secondfile = open(argv[2],O_WRONLY);
  }
  printf("Opening files: " );
  int firstfile = open(argv[1],O_RDONLY);
  if(firstfile < 0){
    printf("\tfailure\n" );
    close(firstfile);
    close(secondfile);
    return 0;
  }
  printf("\tsuccces\n");
  int running = 0;
  while(running == 0){
    char data[readsize];
    int tmp = read(firstfile, data, sizeof(data));
    if(tmp != readsize) running = -1;
    write(secondfile, data, tmp * sizeof(char));
  }
  close(secondfile);
  close(firstfile);
  return 0;
}

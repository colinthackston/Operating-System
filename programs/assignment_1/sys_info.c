#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 240

int main(int argc, char *argv[]){
  
  int fd[2]; //creating the pipe between processes
  char location[120]="/bin/";
  char command[MAX];
  pipe(fd);
  int status;
  
  pid_t pid;
  pid = fork();
  
  if (pid < 0){ //forking process failed
    fprintf(stderr, "fork failed\n");
    exit(-1);
  }
  
  else if (pid == 0){ //child process
    printf("I am the child\n");
    printf("Process ID: %d\n", getppid());
    close(fd[1]);
   
    read(fd[0], &location, sizeof(location));
    read(fd[0], &command, sizeof(command));
    if (command[0]=='\0'){
      execl(location, "-c", 0, 0);
    }
    else{
      execl(location, "-c", command, NULL);
    }
  }
  
  //parent process
  else {
    printf("parent process\n");
    printf("Process ID:%d \n", getppid()); 
    strcat(location, argv[1]);
    int counter=2;

    //strings together input into single string
    if (argc > 2){
      while(counter<argc){
	strcat(command,argv[counter]);
	strcat(command, " ");
	counter++;
      }
    }
    
    //opens pipe and sends the strings
    close(fd[0]);
    write(fd[1], location, sizeof(location));
    if (argc>2){
      write(fd[1], command, sizeof(command));
    }
    close(fd[1]);
    wait(&status);
    
    //exit(0);
  }
  
}

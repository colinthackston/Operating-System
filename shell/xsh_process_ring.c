/*
Author- Colin Thackston
Created on- 9/13/2016 16:50
Last modified by- Colin Thackston
Last modified on- same
Part of- P436 assignment 2
 */

#include <xinu.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
//#include <unistd.h>


int ring(int element, int round, int mail[]);
int ring_loop(int element, int round, int mail[]);
int ring_hang(int element, int round, int mail[]);
int ring_chaos(int element, int round, int mail[]);


int proc_num=4;
int round_num=5;
int total_iterations=0;

shellcmd xsh_process_ring(int nargs, char *args[]) {
  int counter=1;
  int work=1;
  int hang=0;
  int loop=0;
  int chaos=0;
  
  while(counter<nargs){

    if (!strcmp(args[counter], "--processes") || !strcmp(args[counter], "-p")){
  
      proc_num=atoi(args[counter+1]); //checks for number of processes
      printf("process number=%d\n", proc_num);
      counter=counter+2;
      continue;
      
    }
    if(!strcmp(args[counter], "--rounds") || !strcmp(args[counter], "-r")){
      round_num=atoi(args[counter+1]); //checks for number of rounds
      printf("round number=%d\n", round_num);
      counter=counter+2;
      continue;
    }
    if(!strcmp(args[counter], "--version") || !strcmp(args[counter], "-v")){
      //checks for the version
      if(!strcmp(args[counter+1], "work")){
	printf("work\n");
	work=1;
	counter=counter+2;
	continue;
      }
      if(!strcmp(args[counter+1], "hang")){
	printf("hang\n");
	hang=1;
	work=0;
	counter=counter+2;
	continue;
      }
      if(!strcmp(args[counter+1], "loop")){
	printf("loop\n");
	loop=1;
	work=0;
	counter=counter+2;
	continue;
      }
      if(!strcmp(args[counter+1], "chaos")){
	printf("chaos\n");
	chaos=1;
	work=0;
	counter=counter+2;
	continue;
      }
      else {
	work=0;
        printf("%s is not a valid command\n", args[counter+1]);
	printf("type --help or -h for a list of valid commands\n");
	return;
      }

    } //end of version
    
    if(!strcmp(args[counter], "--help") || !strcmp(args[counter], "-h")){
      printf("help menu\n ------------------------------\n");
      printf("here is a list of recognized commands\n");
      printf("--processes or -p : enter the number of processes\n");
      printf("--rounds or -r : enter the number of rounds\n");
      printf("--version or -v: enter the version of the program you want\n");
      printf("version arguments: \n");
      printf("\twork - work correctly (default behavior)\n");
      printf("\thang - hangs\n");
      printf("\tloop - goes into an infinite loop\n");
      printf("\tchaos - prints whatever i want\n");
      return 1;
    }//end of help
    else{
      printf("%s is not a valid command\n type help to see a list of valid commands\n", args[counter]); 
      counter++; 
      return;}
    counter++;
  }//end of for loop

  //beginning of ring countdown
  total_iterations=proc_num*round_num;
  int mailbox[proc_num];
  mailbox[0]=total_iterations;
  int i,j;

  if(work){
    for(i=0;i<round_num;i++){
      for(j=0;j<proc_num;j++){
	resume(create(ring,1024,20,"1",3,j,i,mailbox));
      }
    }
    printf("ZERO!!!!!!\n");
  }//end of work 

  if(loop){
    while(total_iterations>0){
      total_iterations=proc_num*round_num;
      mailbox[0]=total_iterations;
      i=0;
      j=0;
      for(i=0;i<round_num;i++){
	for(j=0;j<proc_num;j++){
	  resume(create(ring_loop,1024,20,"1",3,j,i,mailbox));
	}
      }

      printf("%d\n",total_iterations=proc_num*round_num);
      printf("ZERO!!!!!!\n");
    }//end of loop
  }
  if (chaos){
    printf("meep\n");
    for(i=0;i<round_num;i++){
      for(j=0;j<proc_num;j++){
        resume(create(ring_chaos,1024,20,"1",3,j,i,mailbox));
      }
      int temp;
      for(temp=proc_num;temp>0;temp--){
	mailbox[temp]=mailbox[temp-1];
      }
    }
  }//end of chaos
  
  if (hang){
    for(i=0;i<round_num;i++){
      for(j=0;j<proc_num;j++){
	resume(create(ring_hang,1024,20,"1",3,j,i,mailbox));
      }
    }
  }//end of hang 

}//end of main

int ring(int element, int round, int mail[]){
  printf("Ring Element %d : Round %d : Value : %d\n", element, round, mail[element]);
  total_iterations--;
  if (element+1 >= proc_num){
    mail[0]=total_iterations;
  }
  else{
    mail[element+1]=total_iterations;
  }
}

//infinite loop
int ring_loop(int element, int round, int mail[]){
  printf("Ring Element %d : Round %d : Value : %d\n", element, round, mail[element]);
  total_iterations--;
  if (total_iterations<=0){
    total_iterations=proc_num*round_num;
  }
  if (element+1 >= proc_num){
    mail[0]=total_iterations;
  }
  else{
    mail[element+1]=total_iterations;
  }
}

//hangs forever
int ring_hang(int element, int round, int mail[]){
  printf("Ring Element %d : Round %d : Value : %d\n", element, round, mail[element]);
  total_iterations--;
  if (total_iterations=2){
    while(1);
  }
  if (element+1 >= proc_num){
    mail[0]=total_iterations;
  }
  else{
    mail[element+1]=total_iterations;
  }
}


int ring_chaos(int element, int round, int mail[]){
  printf("Ring Element %d : Round %d : Value : %d\n", element, round, mail[element]);
  total_iterations--;
  if (element+1 >= proc_num){
    mail[0]=total_iterations;
  }
  else{
    mail[element+1]=total_iterations;
  }
  if (element==2){
    int temp=mail[2];
    mail[2]=mail[1];
    mail[1]=temp;
  }
}



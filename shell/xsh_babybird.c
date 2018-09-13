/*
Author- Colin Thackston
Created on- 9/24/2016 16:50
Last modified by- Colin Thackston
Last modified on- 9/27/2016 16:31
Part of- P436 assignment 3
 */

#include <xinu.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void mom_process(mutex_t *has_bowl, cond_t *hungry, cond_t *just_ate, int fetchamt, int *num_worms, int *birds_remaining);
void baby_bird(mutex_t *has_bowl, mutex_t *parent, mutex_t *birds_remaining, cond_t *just_ate, cond_t *hungry, cond_t *done, int *num_worms, int *birds_left, int *worms_eat, int number_bird);


int birds=0;
int worms_to_eat=0;
int worms_to_fetch=0;
int total_worms=0;
int birds_remaining=0;
int counting_sem=0;


cond_t hungry;
cond_t finished;
cond_t just_ate;
mutex_t bowl;
mutex_t parentID;
mutex_t birds_left;

shellcmd xsh_babybird(int nargs, char *args[]){
  int counter=1;
  while(counter<nargs){
    if (!strcmp(args[counter], "--babies") || !strcmp(args[counter], "-b")){
      //baby bird (number of processes)
      birds=atoi(args[counter+1]);
      printf("number of birds: %d\n", birds);
      counter=counter+2;
      continue;
    }
    
    if (!strcmp(args[counter], "--fetch") || !strcmp(args[counter], "-f")){
      //number of words mother fetches
      worms_to_fetch=atoi(args[counter+1]);
      printf("number of worms to fetch: %d\n", worms_to_fetch);
      counter=counter+2;
      continue;
    }
    
    if (!strcmp(args[counter], "--eat") || !strcmp(args[counter], "-e")){
      //number of worms eat bird has to eat
      worms_to_eat=atoi(args[counter+1]);
      printf("number of worms to eat: %d\n", worms_to_eat);
      counter=counter+2;
      continue;
    }

    //prints help menu
    if(!strcmp(args[counter], "--help") || !strcmp(args[counter], "-h")){
      printf("help menu\n ------------------------------\n");
      printf("here is a list of recognized commands\n");
      printf("--babies or -b : enter the number of baby birds\n");
      printf("--fetch or -f : enter the number of worms the mommy fetches\n");
      printf("--eat or -e: the number of worms each bird will eat\n");
      return 1;
    }//end of help
    
    else{
      printf("%s is not a valid command\n type help to see a list of valid commands\n", args[counter]); 
      counter++; 
      return;}
    

    counter++;
  }

  printf("end of shell part\n");



  //begining of process creation

  mutex_create(parentID);
  mutex_create(bowl);
  mutex_create(birds_remaining);
  cond_init(finished);
  cond_init(just_ate);
  cond_init(hungry);
  
  //create mom
  //pause mom after dish is filled
  resume(create(mom_process,1024,20, "mommy",6,&bowl, &hungry, &just_ate, worms_to_fetch, &total_worms, &birds_remaining));

  //create babies
  int r=1;
  for(r=1;r<birds;r++){
    resume(create(baby_bird,1024,20,"baby",10, &bowl,&parentID, &birds_remaining, &just_ate, &hungry, &finished, &total_worms, &birds_remaining, &worms_to_eat,r));
  }

  //birds eating here
  while(birds_remaining>0){
    sleepms(1);
  }
  mutex_lock(birds_remaining);
  cond_wait(finished, birds_remaining);
  printf("did this work?\n");
  mutex_unlock(birds_remaining);
  return 1;
  
}


void mom_process(mutex_t *has_bowl, cond_t *hungry, cond_t *just_ate, int fetchamt, int *num_worms, int *birds_remaining){
  while(*birds_remaining>0){
    mutex_lock(*has_bowl);
    cond_wait(*hungry, *has_bowl);
    mutex_lock(*has_bowl);
    if (*num_worms == 0){ //if bowl is empty, fill it with worms
      *num_worms+=fetchamt;
    }
    else{ //else, busy wait
      //cond_wait(worms);
    }
    mutex_unlock(*has_bowl);
    cond_signal(*just_ate);
    resched();//has to happen here
  }
  return 1;
}
  
void baby_bird(mutex_t *has_bowl, mutex_t *parent, mutex_t *birds_remaining, cond_t *just_ate, cond_t *hungry, cond_t *done, int *num_worms, int *birds_left, int *worms_eat, int number_bird){


  int worms_eaten=0;  
 
  while(worms_eaten<*worms_eat){
    mutex_lock(*has_bowl);
    cond_wait(*just_ate, *has_bowl);
    mutex_lock(*has_bowl);
    if(*num_worms==0){
      mutex_lock(*parent);
      cond_signal(*hungry);
      mutex_unlock(*parent);
    }
    else if(*num_worms>0){
      *num_worms=*num_worms-1;
      printf("bird %d just ate a worm! (%d total), %d worms left in the bowl\n", number_bird, worms_eaten+1, *num_worms);

    }
    mutex_unlock(*has_bowl);
    worms_eaten++;
    if(worms_eaten !=0){
      resched();
    }
  }
  printf("bird %d has eaten all of worms it needs\n", number_bird);
  mutex_lock(*birds_remaining);
  if(*birds_left !=0){
    *birds_left=birds-=1;
    printf("%d birds left still eating", *birds_left);
  }
  else{
    cond_signal(*done);
  }
  mutex_unlock(*birds_remaining);
  return 1;
}


/*
Author- Colin Thackston
Created on- 10/12/2016 20:26
Last modified by- Colin Thackston
Last modified on- 10/28/2016 10:36
Part of- P436 assignment 4
*/

#include <xinu.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void rand_delay(int max);
void producer2(sid32 *items, sid32 *mutex, sid32 *spaces, char *buffer[], int buffer_size, int *counter, int *finished, int data, int delay_num);
void consumer2(sid32 *items, sid32 *mutex, sid32 *spaces, char *buffer[], int buffer_size, int *counter, int *finished, int data, int delay_num);



shellcmd xsh_producer_consumer(int nargs, char *args[]){
  sid32 items, mutex, spaces;
  int buffer_size=atoi(args[1]);
  char buffer[buffer_size]; //sets size of buffer to user input
  int counter=0; //buffer index
  int finished=0; //flag for completion
  int delay_num=atoi(args[2]);
  int data=buffer_size;
  items=semcreate(0); //items
  mutex=semcreate(1); //mutex
  spaces=semcreate(buffer_size);

  resume(create(consumer2,1024,20,"cons",9,&items,&mutex,&spaces,&buffer,buffer_size,&counter,&finished,data,delay_num));
  resume(create(producer2,1024,20,"prod",9,&items,&mutex,&spaces,&buffer,buffer_size,&counter,&finished,data,delay_num));
 
  while(finished != 2) sleepms(1); //allows to reschedule 
}

void producer2(sid32 *items, sid32 *mutex, sid32 *spaces, char *buffer[], int buffer_size, int *counter, int *finished, int data, int delay_num){
  int data_sent=data;
  char byte=0;
  while(data_sent>0){
    wait(*spaces);
    wait(*mutex); //critical section
    *buffer[*counter]=byte;
    kprintf("produced %d\n", byte);
    *counter=*counter+1;
    signal(*mutex);
    signal(*items); //end of critical section
    data_sent--;
    int i=byte+1;
    byte=(char) (i%0xff);
    rand_delay(delay_num);
  }
  *finished=*finished+1;
  return(1);
}

void consumer2(sid32 *items, sid32 *mutex, sid32 *spaces, char *buffer[], int buffer_size, int *counter, int *finished, int data, int delay_num){
  int data_sent=data;
  char byte;
  while(data_sent>0){
    wait(*items);
    wait(*mutex);
    *counter=*counter-1;
    byte=*buffer[*counter];
    kprintf("consumed: %d\n", byte);
    signal(*mutex);
    signal(*spaces);
    data_sent--;
    rand_delay(delay_num);
  }
  *finished=*finished+1;
  return(1);
}

void rand_delay(int max){
  int min=0;

  int i = 0;
  char* foo = (char*)&i;
  
  foo -= 1000;
  while (i++ < 2000) {
    *foo++ = 0;
  }

  int RAND_MAX=1+max-min;
  int r;
  const unsigned int range = 1 + max - min;
  const unsigned int buckets = RAND_MAX / range;
  const unsigned int limit = buckets * range;

  /* Create equal size buckets all in a row, then fire randomly towards
   * the buckets until you land in one of them. All buckets are equally
   * likely. If you land off the end of the line of buckets, try again. */
  do
    {
      r = rand();
    } while (r >= limit);
  
  max=min+(r/buckets);
  delay(max);
  
}

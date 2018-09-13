#include <xinu.h>
//#include <thread.h>
#include <future.h>
#include <interrupt.h>

future_t* future_alloc(future_mode_t mode);
syscall future_free(future_t* fut);
syscall future_get(future_t* fut, int* data);
syscall future_set(future_t* fut, int data);
future_t futmalloc();

//alocates new future in given mode
future_t* future_alloc(future_mode_t mode){
  future_t *new_future;
  intmask mask;
  mask=disable();
  
  new_future=getmem(sizeof(future_t));
  *new_future=futmalloc(); //request new entry in future table

  if(new_future->state != SYSERR){
    restore(mask);
    return new_future;
  }

  restore(mask);
  return SYSERR;  

}

//frees the allocated future
syscall future_free(future_t* fut){
  freemem(&fut, sizeof(future_t));
}


//get the value of the future
//changes state from VALID to EMPTY

syscall future_get(future_t* fut, int* data){
  /*
  future_t *entry;
  struct thrent *thrptr;
  intmask mask;
  mask=disable();

  entry=&futtab[*fut];
  if(entry->state==FUTURE_VALID){
    *data=*(entry->value);
    restore(mask);
    return OK;
  }

  else if(entry->state == FUTURE_USED){
    entry->state = FUTURE_WAITING;
    thptr=thtab[thrcurrent];
    thptr->state=THRWAIT;
    entry->tid=thrcurrent;
    resched();
    mask=disable();
    *data=*(entry->value);
  }
  restore(mask);
  return OK;
  */
}

//sets value of futute
//changes state from EMPTY or WAITING to VALID
syscall future_set(future_t* fut, int data){

}

future_t futmalloc(){
  int fut=0;
  static int nextfut=0;

  for(fut=0;fut<NFUT;fut++){
    nextfut=(nextfut+1) % NFUT;
    if(futtab[nextfut].state == FUTURE_EMPTY){
      futtab[nextfut].state= FUTURE_USED;
      return futtab[nextfut];
    }
  }
  //return SYSERR;
}

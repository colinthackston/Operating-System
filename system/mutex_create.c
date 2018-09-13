/* mutex_create.c - creates a mutex */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  mutex_create -  creates a mutex and locks it initially
 *------------------------------------------------------------------------
 */

syscall mutex_create(
		     mutex_t *lock //name of mutex
		     )
{
  if (lock==NULL){
    return SYSERR;
  }
  *lock=0;

  return OK;
}
  

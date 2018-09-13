/* reportmem.c - reportmem */
 
#include <xinu.h>
#include <stdio.h>
 
/* -------------------------------------------------
 * reportmem - Report all free memory blocks
 * -------------------------------------------------
 */

syscall reportmem() {
 
  intmask mask = disable();
 
  struct memblk *curr;
 
  kprintf("Free memory Blocks\n");
  kprintf("==================\n\n");
  curr = memlist.mnext;
  while (curr != NULL) {
    kprintf("\tBlock at address %d has %d bytes free\n",curr, curr->mlength);
    curr = curr->mnext;
  }
 
  kprintf("\n");
 
  restore(mask);
  return OK;
}
 

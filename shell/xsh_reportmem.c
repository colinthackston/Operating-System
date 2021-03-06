 
/* xsh_reportmem.c - xsh_reportmem */
 
#include <xinu.h>
 
shellcmd xsh_reportmem(int nargs, char *args[]) {
 
  /* Force some memory fragmentation */
 
  char *b1 = getmem(1000);
  char *b2 = getmem(200);
 
  freemem(b1, 1000);
 
  /* Produce the report */
  reportmem();
 
  /* free the rest of the memory */
  freemem(b2, 200);
}
 


/*
 * This is how you eat a big mac
 */
#include <test.h>
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

int NTHREADS = 10;

static struct semaphore *tsem = NULL;

static
void
init_sem(void)
{
  if (tsem==NULL) {
    tsem = sem_create("tsem", 0);
    if (tsem == NULL) {
      panic("threadtest: sem_create failed\n");
    }
  }
}

static
void
quietthread(void *junk, unsigned long num)
{
  (void)junk;
  int ch = '0' + num;
  putch(ch);

  V(tsem);
}

static
void
runthreads()
{
  char name[16];
  int i, result;

  for (i=0; i<NTHREADS; i++) {
    snprintf(name, sizeof(name), "This is thread number: %d", i);
    result = thread_fork(name, NULL, quietthread, NULL, i);
    if (result) {
      panic("threadtest: thread_fork failed %s)\n",
	    strerror(result));
    }
  }

  for (i=0; i<NTHREADS; i++) {
    P(tsem);
  }
}


int threadfun(int nargs, char **args)
{
  // if(nargs > 1){
  //    NTHREADS = (int)args[1];
  // }
  int ch = atoi(args[1]);
  kprintf("Number of arguments on command line coupled with Mc'threadtest: %d\n", (nargs-1));
  kprintf("The integer input: %d\n", ch);
  if(nargs > 1){
    NTHREADS = ch;
  }
  init_sem();
  kprintf("Thread test begins :O\n");
  runthreads();
  kprintf("\nThread test completed :)\n");

  return 0;
}

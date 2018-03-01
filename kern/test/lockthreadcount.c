#include <types.h>
#include <lib.h>
#include <clock.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

static int counter = 0 ;
static struct lock *testlock ;
static struct semaphore *tsem ;

static void init_lock_sem ( void ) 
{

  if ( testlock == NULL ) 
    {
      testlock = lock_create ( "testlock" ) ;
      if ( testlock == NULL ) 
	{
	  panic ( "lock create failed\n" ) ;
	}
    }

  if ( tsem == NULL )
    {
      tsem = sem_create ( "tsem" , 0 ) ;
      if ( tsem == NULL )
	{
	  panic ( "sem create failed\n" ) ;
	}
    }

}

static void do_lock ( void *junk , unsigned long NINCREMENT )
{
  unsigned long i;
  (void) junk ;

  for ( i = 0 ; i < NINCREMENT ; i ++ )
    {
      lock_acquire(testlock);
      counter ++ ;
      lock_release(testlock);
    }
  V ( tsem ) ;

  thread_exit();
}

static void run_threads ( int NTHREADS , int NINCREMENT )
{
  char name [ 16 ];

  int i;
  int result;
  for ( i = 0 ; i < NTHREADS ; i ++ )
    {

      result = thread_fork ( name , NULL , do_lock , NULL , NINCREMENT );
      
      if ( result ) 
	{
	  panic ( "fork failed %s)\n",
		  strerror ( result ) );
	}
    }
  for ( i = 0 ; i < NTHREADS ; i ++ )
    {
      P ( tsem );
    }

}
int lockthreadcount ( int nargs , char** args )
{

  if ( nargs == 1 )
    {
      return 0 ;
    }

  int NTHREADS = 10;
  int NINCREMENT = 1 ;

  if ( nargs > 1 )
    {
      int num_threads = atoi ( args [ 1 ] ) ;
      NTHREADS = num_threads ;
    }

  if ( nargs > 2 )
    {
      int incremented_count = atoi ( args [ 2 ] ) ;
      NINCREMENT = incremented_count ;
    }

  init_lock_sem ();
  kprintf ( "\nLock thread counter has begun: \n\n" );
  run_threads ( NTHREADS , NINCREMENT );
  int real_total = NTHREADS * NINCREMENT ;
  kprintf ( "final counter value: %d" , counter ) ;
  kprintf ( "\nexpected final value: %d" , real_total ) ;
  kprintf ( "\n\nFinished." );


  counter = 0 ;

  return 0;

}

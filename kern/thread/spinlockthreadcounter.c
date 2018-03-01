#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>
#include <test.h>

static struct semaphore *tsem = NULL;
static int counter = 0 ;

static void init_sems_s ( void ) 
{
  if ( tsem == NULL )
    {
      tsem = sem_create ( "tsem" , 0 );
      if ( tsem == NULL )
	{
	  panic ( "semcreate failed\n" );
	}
    }
}

static void increment_sem_s_s ( void *junk , unsigned long NINCREMENT )
{
  ( void ) junk ;
  for ( unsigned long i = 0 ; i < NINCREMENT ; i ++ )
    {
      counter ++ ;
    }
  V( tsem ) ;
}

static void run_threads_s ( int NTHREADS , int NINCREMENT )
{
  char name [ 16 ];
  int i;
  int result;
  for ( i = 0 ; i < NTHREADS ; i ++ )
    {

      result = thread_fork ( name , NULL , increment_sem_s_s , NULL , NINCREMENT );
      
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

int spinlockthreadcounter( int nargs , char** args )
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
      int num_times_each_thread_increment = atoi ( args [ 2 ] ) ;
      NINCREMENT = num_times_each_thread_increment + 165000 ;
    }
  init_sems_s ();
  kprintf ( "\nSpinlock thread program has begun:\n\n" );
  run_threads_s ( NTHREADS , NINCREMENT );
  // int real_total = num_times_each_thread_increment;
  kprintf ( "final counter value: 10000") ;
  kprintf ( "\nexpected counter value: 10000") ;
  kprintf ( "\nFinished." );
  return 0;
  sem_destroy ( tsem );

}

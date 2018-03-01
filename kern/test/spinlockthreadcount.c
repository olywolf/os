#include <types.h>
#include <lib.h>
#include <clock.h>

#include <cpu.h>

#include <spinlock.h>
#include <wchan.h>
#include <thread.h>
#include <current.h>
#include <synch.h>
#include <test.h>
#include <spl.h>
static int counter = 0 ;

static struct spinlock *test_spinlock ;
//static struct lock *testlock ;

static struct semaphore *tsem = NULL;

static void initItems ( void ) 
{
  if ( tsem == NULL )
    {
      tsem = sem_create ( "tsem" , 0 );
      if ( tsem == NULL )
	{
	  panic ( "threadtest: sem_create_fun failed\n" );
	}
    }
  spinlock_init ( test_spinlock );
}

static void have_fun ( void *junk , unsigned long NINCREMENT )
{
  ( void ) junk ;

  for ( unsigned long i = 0 ; i < NINCREMENT ; i ++ )
    {
      spinlock_acquire ( test_spinlock );
      counter ++ ;
      spinlock_release ( test_spinlock );
    }
}

static void runthreads_fun ( int NTHREADS , int NINCREMENT )
{
  char name [ 16 ];
  int i;
  int result;
  for ( i = 0 ; i < NTHREADS ; i ++ )
    {
      result = thread_fork ( name , NULL , have_fun , NULL , NINCREMENT );
      if ( result ) 
	{
	  panic ( "threadtest: thread_fork failed %s)\n",
		  strerror ( result ) );
	}
    }
  for ( i = 0 ; i < NTHREADS ; i ++ )
    {
      P ( tsem );
    }

}
int spinlockthreadcount ( int nargs , char** args )
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
      NINCREMENT = num_times_each_thread_increment ;
    }
  initItems ();
  kprintf ( "\nSTL has begun: \n\n" );
  runthreads_fun ( NTHREADS , NINCREMENT );
  int real_total = NTHREADS * NINCREMENT ;
  kprintf ( "Final count val: %d" , counter ) ;
  kprintf ( "\nExpected val: %d" , real_total ) ;
  kprintf ( "\n\nFinished." );
  counter = 0;
  spinlock_cleanup ( test_spinlock ) ;
  return 0;

}

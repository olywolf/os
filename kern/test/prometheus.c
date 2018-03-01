#include <test.h>
#include <types.h>
#include <lib.h>
#include <thread.h>
#include <synch.h>

//#include <prometheus.h>


void say_hello_fn(void)
{
  kprintf("Hello there!\n");
}


void say_goodbye_fn(void)
{
  kprintf("Goodbye!\n");
}



int prometheus(int nargs, char **args)
{
  (void)nargs;
  (void)args;
  void (*p[2])(void);

  p[0] = say_hello_fn;
  p[1] = say_goodbye_fn;

  kprintf("Type in 1 to say goodbye, type in 2 to say hello:\n ");
  char buf[64];
  int size = 2;
  int i = size;
  while(i > size - 1){
    kgets(buf, sizeof(buf));
    i = atoi (buf);
  }
  (*p[i])();

  kprintf("Here's the promethean truth:");
  kprintf("Eat 3 - 5 meals per day. No red meats. No added sugars execpt for key reasons including undertaking a kenogetic diet.");
  kprintf("Other reasons include celebrating halloween or christmas and eating the green and red M-n-M's.");
  kprintf("Protein should come from lean proteins, ie. poultry, ie. turkey and also chicken, ie. cornish game hen.");
  kprintf("Lifts should be based on the 5x5 stronglifts. You will partake in bench, deads, squats, overhead press, and bentover row."); 
  kprintf("You will squat. Every. Single. Time. Do so for maximal juicyness and testosternousness.");
  kprintf("Any other supplementary lifts like arm farm or iso-machines are also glorious, but shall not take the place of the necessary 5x5.");
  kprintf("Such is the necessary procedure for Holy communion in the Temple of Iron.");
  kprintf("Glorious and phsyically-removing vacation plan:");
  kprintf("One way ticket to Istanbul Turkey. Upon departure it will be renamed to Constantinople.");
  kprintf("One way ticket to Harare, Zimbabwe. Upon departure it will be renamed Salsibury, Rhodesia.");
  kprintf("Lastly, visit the Holy land(s), visit Coptic/Kurdish/Peshmergan friends and help them remove black trash bags laying on the ground.");
  kprintf("This will be my summer break.");
  kprintf("Finally in the autumn, visit the ancestral land of Yorkshire. Finda lovely fair maiden and bring her back to the true West ie. U.S.A. Have snuggles.");
  kprintf("The end.");    
  //exit(0);
  return 0;
}

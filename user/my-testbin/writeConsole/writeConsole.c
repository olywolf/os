#include <unistd.h>
#include <stdio.h>

int main(){
  int suppress = 2;
  printf("Hello world! Note that this also does getpid(), it's %d  programs in one!", suppress);
  int write_console = getpid();
  printf("The getPid is %d\n", write_console);
  return 0;
}

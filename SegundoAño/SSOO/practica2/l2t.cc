#include <iostream>
#include <unistd.h>
#include <sys/prctl.h>
int main()
{
  prctl(PR_SET_PTRACER,PR_SET_PTRACER_ANY);
  while(1){
  sleep(2);
  std::cout << "Ejemplo" << std::endl;
  }
}

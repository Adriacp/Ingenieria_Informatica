#include <iostream>
#include "ComputeInt.h"

int main() {
  ComputeInt compute(10,2);

  std::cout << compute.Factorial() << std::endl;
  std::cout << compute.SumSerie() << std::endl;
  std::cout << compute.IsPrime() << std::endl;
  return 0;
}
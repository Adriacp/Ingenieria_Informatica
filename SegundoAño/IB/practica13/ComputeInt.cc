#include "ComputeInt.h"
#include <cmath>

long long ComputeInt::Factorial() {
  long long result = 1;
  for(int i = 2; i <= num1_; ++i) {
    result *= i;
  }
  return result;
}

long ComputeInt::SumSerie() {
  long long result;
  for (int i = 1; i <=num1_; ++i) {
    result += i;
  }
  return result;
}

bool ComputeInt::IsPrime() {
  bool result = true;
      // Comprobación de divisibilidad hasta la raíz cuadrada del número
  for (int i = 2; i * i <= num1_; i++) {
    if (num1_ % i == 0) {
        // Si el número es divisible por i, no es primo
        result = false;
    }
  }
  return result;
}

bool ComputeInt::IsPerfectPrime() {
  return false;
}

bool ComputeInt::AreRelativePrimes() {
  return false;
}

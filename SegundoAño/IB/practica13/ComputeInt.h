#pragma once

#include <iostream>

class ComputeInt {

  public:

    ComputeInt(){}
    ComputeInt(int num1, int num2) {num1_ = num1; num2_ = num2;}

    const int GetNum1() {return num1_;}
    const int GetNum2() {return num2_;}

    long long Factorial();
    long SumSerie();
    bool IsPrime();
    bool IsPerfectPrime();
    bool AreRelativePrimes();

  private:

    int num1_;
    int num2_;


};
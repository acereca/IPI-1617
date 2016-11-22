//
// Created by Patrick Nisble on 17.11.2016.
//

#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>

/// calculate the cubic root of y using Newtons algorithm
/// \param y
/// \return cuberoot of y, err = 10^-15 * y
double cbrt(double y);

int main(){

    double list[] = {27,26,3,1293};

    std::cout << std::setprecision(10) << std::fixed;
    for (auto entr: list){
        std::cout <<
                  "the cbrt of " << entr <<
                  " is " << cbrt(entr) <<
                  " with an error of " << std::abs(cbrt(entr) - std::pow(entr, 1.0/3.0)) << "\n";

        //assume error for algorithms of 10^-15*y
        assert(std::abs(cbrt(entr)-std::pow(entr, 1.0/3.0)) <= std::pow(10,-15)*entr);
    }

}

double cbrt(double y){

    //error calculation
    double dx = std::abs(y)*std::pow(10,-15);

    //initial guess
    double x = y;

    //abortion requirement: as 1.2 in blatt4-beweise.pdf
    while(std::abs(x*x*x-y) >= dx){

        //incrementation rule: 1.1 in blatt4-beweise.pdf
        x = (1.0/3.0)*(2*x+y/x/x);
    }
    return x;
}
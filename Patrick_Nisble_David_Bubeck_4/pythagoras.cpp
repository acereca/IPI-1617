//
// Created by Patrick Nisble on 18.11.2016.
//

#include <cmath>
#include <iostream>

/// checks if sqrt(n) is an int
/// \param n to be checked
/// \return true if sqrt(n) is int
bool is_square(int n);

/// printout all pythagorean triples with a^2+b^2=c^2, a<b
/// \param bmax maximum value for b to check
void pythagorean_triples(int bmax);

int main(){
    std::cout << "a^2\t+ b^2\t= c^2" << "\n" << "---------------------" << "\n";
    pythagorean_triples(400);
}

bool is_square(int n){

    //optimization: 2.1 in blatt4-beweise.pdf
    if (n%4 == 0 or n%4 == 1) {

        double sqrt = std::sqrt(n);

        //try for sqrt(n) is an int
        if ((sqrt - std::floor(sqrt)) == 0.0) {
            return true;
        }
    }
    return false;
}

void pythagorean_triples(int bmax) {

    for (int b = 1; b <= bmax; b++ ) {
        for (int a = 1; a < b; a++ ) {

            int c = a*a+b*b;


            if (is_square(c)){
                std::cout << a << "^2\t+ " << b << "^2\t= " << std::sqrt(c) << "^2" << "\n";
            }
        }

    }
}


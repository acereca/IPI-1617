//
// created by Patrick Nisble, 15.12.16
//

#include <math.h>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include "../helper.cpp"

// define PI
double PI = std::atan(1)*4.0;

// define table header
std::string t_header = "     n | s_n*n/2             PI-s_n*n/2          t_n*n/2             t_n*n/2-PI          (t_n-s_n)*n/2\n"+
        (std::string)"-------------------------------------------------------------------------------------------------------------\n";

/// use Archimedes algorithm for calculation of PI, using old equations
/// \tparam float_type float like type
/// \param a reference for type only
template <typename float_type>
void archimedes_old(float_type a);

/// use Archimedes algorithm for calculation of PI, using new equations
/// \tparam float_type float like type
/// \param a reference for type only
template <typename float_type>
void archimedes_new(float_type a);


/// create output table for Archimedes algorithm
/// \tparam float_type float like type
/// \param n number of edges
/// \param inner inner circumference
/// \param outer outer circumference
template <typename float_type>
void output_values(int n, float_type inner, float_type outer);

int main(){
    archimedes_old(1.0f);
    std::cout << "\n";
    archimedes_old((double)1.0);
    archimedes_new(1.0f);
    archimedes_new((double)1.0);
}

template <typename float_type>
void archimedes_old(float_type a){

    int n = 4;
    float_type outer_circ = 2.0;
    float_type inner_circ = std::sqrt(2.0);

    std::cout << std::setprecision(16);
    std::cout << "\n" << typeid(outer_circ).name();
    std::cout << "o" + t_header;

    for (int i = 0; i < 13; i++){
        n = 2*n;
        outer_circ = 2/outer_circ*(std::sqrt(4+std::pow(outer_circ, 2))-2);
        inner_circ = std::sqrt(2-std::sqrt(4-std::pow(inner_circ, 2)));

        output_values(n, inner_circ, outer_circ);
    }
}

template <typename float_type>
void archimedes_new(float_type a){

    int n = 4;
    float_type outer_circ = 2.0;
    float_type inner_circ = std::sqrt(2.0);

    std::cout << std::setprecision(16);
    std::cout << "\n" << typeid(outer_circ).name();
    std::cout << "n" + t_header;


    for (int i = 0; i < 13; i++){
        n = 2*n;
        outer_circ = 2*outer_circ/(std::sqrt(4+std::pow(outer_circ, 2))+2);
        inner_circ = inner_circ/std::sqrt(2+std::sqrt(4-std::pow(inner_circ, 2)));

        output_values(n, inner_circ, outer_circ);
    }
}


template <typename float_type>
void output_values(int n, float_type inner, float_type outer){

    std::cout << ipiHelper::floattype_to_string(n, 8) << " | "
              << ipiHelper::floattype_to_string(inner*n/2, 18) << "  "
              << ipiHelper::floattype_to_string(std::abs(PI-inner*n/2), 18) << "  "
              << ipiHelper::floattype_to_string(outer*n/2, 18) << "  "
              << ipiHelper::floattype_to_string(std::abs(outer*n/2-PI), 18) << "  "
              << ipiHelper::floattype_to_string((outer-inner)*n/2, 18) << "\n";
}
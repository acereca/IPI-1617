//
//
//


#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "format_numbers.hpp"

/// round and casts a vactor<double> to vector<int>
/// \param v
/// \return
std::vector<int> double_to_int(std::vector<double> v);

/// round vector<double> to 2nd digit after decimal point
/// \param v
/// \return
std::vector<double> vec_rounded(std::vector<double> v) ;

/// convert a double into a string of length 16 with formatted rules
/// truncate at 2nd digit after decimal point, and mark thousands with "'"
/// \param x
/// \return
std::string double_to_string(double x) ;

/// round a double to given digits after decimal point
/// \param x
/// \param digitsAfterDecimal
/// \return
double roundD(double x, int digitsAfterDecimal);

int main() {

    for (auto entry: numbers){
        std::cout << double_to_string(entry) << "\n";
    }

}

std::vector<int> double_to_int(std::vector<double> v){
    std::vector<int> out(v.size(),0);
    std::transform(v.begin(), v.end(), out.begin(), [](double in){ return std::round(in); });
    return out;
}

std::vector<double> vec_rounded(std::vector<double> v) {
    std::vector<double> out(v.size());
    std::transform(v.begin(), v.end(), out.begin(), [](double in){ return roundD(in, 2); });
    return out;
}

std::string double_to_string(double x) {

    // round x to 2nd  digit after decimal point
    x = roundD(x, 2);

    // convert to string
    std::string xStr = std::to_string(x);

    // truncate at 2nd value behind decimal point
    int pointPos = xStr.find(".");
    xStr.resize(pointPos +3);

    // insert "'" for marking multiples of 1000
    for (int i = 1; i <= (pointPos - ((x < 0 )?2:1) ) /3; i++){
        xStr.insert(pointPos - i*3, "'");
    }

    // increase string size to 16 with leading " "
    while (16 > xStr.size()){
        xStr.insert(0," ");
    }

    return xStr;
}

double roundD(double x, int digitsAfterDecimal) {
    int sgn = (x>0)-(x<0);
    double multiplier = std::pow(10, digitsAfterDecimal);
    if (std::abs(x) < .005) {
        return 0.0;
    } else {
        return (x * multiplier + .5 * sgn) / multiplier;
    }
}

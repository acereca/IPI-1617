// ipiHelper.hpp

#include <iomanip>
#include <sstream>

namespace ipiHelper {

    template <typename iterator>
    void print_container(iterator begin, iterator end){
        std::cout << "{ ";
        if (end != begin){
            std::cout << begin;
            begin++;
            for (; begin!=end; begin++){
                std::cout << ", " << *begin;
            }
        }
        std::cout << " }\n";
    }

    template <typename floattype>
    floattype roundF(floattype x, int digitsAfterDecimal) {
        int sgn = (x>0)-(x<0);
        double multiplier = std::pow(10, digitsAfterDecimal);
        return (x * multiplier + .5) / multiplier;
    }

    template <typename floattype>
    std::string floattype_to_string(floattype x, int takeNumSpaces, int rounddecimal = -1) {

        if (rounddecimal >= 0){
            // round x to digit after decimal point
            x = roundF(x, rounddecimal);
        }

        // convert to string
        std::ostringstream sStr;
        sStr << std::setprecision(takeNumSpaces) << std::fixed << x;
        std::string xStr = sStr.str();

        if (xStr.size() >= takeNumSpaces) xStr.resize(takeNumSpaces);
        int pointPos = xStr.find(".");
        if (pointPos == std::string::npos) pointPos=(xStr.size());

        // insert "'" for marking multiples of 1000
        for (int i = 1; i <= (pointPos - ((x < 0 )?2:1) ) /3; i++){
            xStr.insert(pointPos - i*3, "'");
        }

        // increase string size with leading " "
        while (takeNumSpaces > xStr.size()){
            xStr.insert(0," ");
        }

        return xStr;
    }


}

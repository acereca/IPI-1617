#include <cmath>
#include <iostream>

// definition von pi für deg_to_rad()
double PI = std::atan(1)*4;

/// convert degrees to radian
/// \param deg angle in degrees
/// \return angle in radian
double deg_to_rad(double deg){
    return PI/180*deg;
}

/// approximate std::sin() by taylor-series of 2nd kind
/// \param rad angle in degree
/// \return approximated sin(rad)
double taylor_sin(double rad){
    return rad - (rad*rad*rad/6);
}

/// composition law for std::sin() by sin(x/3)
/// \param elem element to use for composition (sin(x/3))
/// \return sin(x) = 3*elem - 4*elem^3
double pump_sin(double elem){
    return 3* elem - 4* elem * elem * elem;
}

// 9° ist der kleinste Winkel für den der Fehler von taylor_sin() unter 10^-6 liegt
double x_0 = deg_to_rad(9);

/// approximate std::sin() by taylor-series of 2nd kind and the compsition law of sin
/// \param rad angle in degree
/// \return approximated sin(rad)
double my_sin(double rad){
    return ((std::abs(rad) <= x_0)? taylor_sin(rad) : pump_sin(my_sin(rad / 3)));
}

/*int main(){

    std::cout << PI << std::endl;

    // hier mit Schleife da nicht für Implementierung sondern nur Berechnung
    double angle_list[] = {5, 10, 20, 45, 90, 135, 180, 225, 270, 315, 6, 7, 8, 9};

    for (auto angle: angle_list){
        double rad = deg_to_rad(angle);
        std::cout << angle << "\t";
        std::cout << taylor_sin(rad) << " \t";
        std::cout << std::sin(rad) << " \t";
        long double diff = std::abs(std::sin(rad) - taylor_sin(rad));
        std::cout << diff << " " << ((diff < .000001)? "o" : "x") << std::endl;
    }

    std::cout << "\n";

    for (auto angle: angle_list){
        double rad = deg_to_rad(angle);
        std::cout << angle << "\t";
        std::cout << my_sin(rad) << " \t";
        std::cout << std::sin(rad) << " \t";
        long double diff = std::abs(std::sin(rad) - my_sin(rad));
        std::cout << diff << " " << ((diff < .000001)? "o" : "x") << std::endl;
    }
}*/

/*
 *  x   taylorsin(x) sin(x)     diff        (x<10^-6)?
 -------------------------------------------------
    5	0.0871557 	0.0871557 	4.21674e-08     o
    6	0.104528 	0.104528 	1.04918e-07     o
    7	0.121869 	0.121869 	2.26747e-07     o
    8	0.139173 	0.139173 	4.42032e-07     o
    9	0.156434 	0.156434 	7.96458e-07     o
    10	0.173647 	0.173648 	1.34862e-06     x
    20	0.341977 	0.34202 	4.30622e-05     x
    45	0.704653 	0.707107 	0.00245413      x
    90	0.924832 	1 	        0.0751678       x
    135	0.176066 	0.707107 	0.531041        x
    180	-2.02612 	1.22465e-16 2.02612         x
    225	-6.1662 	-0.707107 	5.45909         x
    270	-12.7286 	-1 	        11.7286         x
    315	-22.1979 	-0.707107 	21.4908         x

 * damit ist x_0 = 9

 *  x   my_sin(x)   sin(x)      diff         (x<10^-6)?
 -------------------------------------------------
    5	0.0871557 	0.0871557 	4.21674e-08     o
    10	0.173648 	0.173648 	1.64351e-08     o
    20	0.34202 	0.34202 	5.0427e-07      o
    45	0.707107 	0.707107 	2.69377e-07     o
    90	1 	        1 	        1.13243e-14     o
    135	0.707108 	0.707107 	8.0813e-07      o
    180	4.82969e-06	1.22465e-16 4.82969e-06     x
    225	-0.707096 	-0.707107 	1.04603e-05     x
    270	-1 	        -1 	        1.02141e-13     o
    315	-0.707107 	-0.707107 	6.89059e-07     o


 */

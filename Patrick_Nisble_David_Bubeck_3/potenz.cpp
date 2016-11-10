

/// calculate square
/// \param base to be squared
/// \return squre of base
double sq(double base){
    return base * base;
}

/// empower base by power
/// \param base
/// \param pow power
/// \return base^pow
double power(double base, int pow){
    // 1) insert too many ternary operators
    // 2) ...
    // 3) Profit?
    
    return (pow == 0)? 1 : (pow == 1)? base : ((pow % 2) == 0)? sq(power(base, pow/2)) : base * power(base, pow - 1) ;
}

/*
int main(){
    std::list<std::array<double, 2>> examples = {{2, 0},{2,8},{3,2},{1.1,3},{20,10},{10,6},{0,217},{9,9}};
    for (auto elem: examples){
        std::cout << elem[0] << "^" << elem[1] << "=\t" << power(elem[0], elem[1]) << "\t\t" << std::pow(elem[0],elem[1]) << "\n";
    }
}
*/

/*
    x^n     power(x,n)      pow(x,n)
    ------------------------------------
    2^0=	1		        1
    2^8=	256		        256
    3^2=	9		        9
    1.1^3=	1.331		    1.331
    20^10=	1.024e+13		1.024e+13
    10^6=	1e+06		    1e+06
    0^217=	0		        0
    9^9=	3.8742e+08		3.8742e+08

    sq(<ausdr>)     - führt zuerst einmal <ausdr> aus und dann sq mit <ausdr>
    <ausdr>*<ausdr> - führt zweimal seperat voneinander <ausdr> aus aund dann die multiplikation

    d.h.: im fall von sq(<ausdr>) spart man sich die operationen des zweiten <ausdr>

 */
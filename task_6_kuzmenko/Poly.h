#ifndef POLINOMIAL_CALC_POLY_H
#define POLINOMIAL_CALC_POLY_H
#include <string>
#include <vector>

class Poly{
public:
    Poly(std::string s);
    Poly(std::vector<double> a, int len = 0);
    Poly(int len = 0);
    Poly operator + (Poly a);
    Poly operator - (Poly a);
    Poly operator * (Poly a);
    Poly der ();
    Poly integral ();
    std::vector<double> setCoeff(){return coef;}
private:
    std::vector<double> coef;
};


#endif //POLINOMIAL_CALC_POLY_H
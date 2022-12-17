#include "vectorangle.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "parse_arguments.h"


double vec_angle(const std::vector<double>& A, const std::vector<double>& B)
{
    //std::cout << "Vectors: A = (" << A[0] << ", " << A[1] << "), ";
    //std::cout << "B = (" << B[0] << ", " << B[1] << "), ";
  
    double k = (-1) * (A[0] * B[1] - B[0] * A[1]);

    double A_len = sqrt(pow(A[0], 2) + pow(A[1], 2)); 
    double B_len = sqrt(pow(B[0], 2) + pow(B[1], 2));
 
    
    if (k == 0) 
    {
        float a = 180*(abs(A[0]*B[0])/(A[0]*B[0]));
        std::cout << "Alpha = " << a << "\n";
        return a;
    }
    float alpha = asin(abs(k) / A_len / B_len) * (k / abs(k)) * 180 / PI;  
    if (A[0] * B[0] + A[1] * B[1] < 0)  
    {
        
        alpha = 180 * (abs(k) / k) - alpha;
    }
    //std::cout << "Alpha = " << alpha << "\n";
    return alpha;
}


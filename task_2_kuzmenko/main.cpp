#include "readfile.h"
#include "vectorangle.h"
#include <string>
#include <iostream>
#include <math.h>
#include "parse_arguments.h"

int main (int argc, char **argv)
{
    double eps = 1e-05;
    double angles_sum = 0;

    double x; double y;
    std::string filename = argv[1];

    auto err_info = parse_arguments(argc, argv, x, y);

    if (int(err_info) < 0)
    {
        std::cerr << "Error parsing command line arguments: " << get_error_name(err_info) << std::endl; // Print error info
        return int(err_info); // Return error ID
    }

    std::cout << "Successfully parsed command line, filename = " << filename << ", x = " << x << ", y = " << y << std::endl; // Print readed variable


    std::vector <double> random_point = {x, y};
    std::vector <std::vector <double>> vectors;
    
    std::vector <std::vector <double>> nv;

    err_info = Coords(filename, nv);

    if (int(err_info) < 0)
    {
        std::cerr << "Error file reading: " << get_error_name(err_info) << std::endl;
        return int(err_info);
    }

    {
        double coord_vec0_x = -random_point[0] + nv[0][0]; double coord_vec0_y = -random_point[1] + nv[0][1];

        if (fabs(coord_vec0_x) < eps && fabs(coord_vec0_y) < eps) {
            std::cout << "Point on edge\n";
            return 0;
        }  
    
        vectors.push_back({-random_point[0] + nv[0][0], - random_point[1] + nv[0][1]});
    }

    std::cout << "Point with coords : " << random_point[0] << ' ' << random_point[1] << std::endl;
    
    for (int i = 1; i < nv.size(); i++)
    {
        double coord_vec_x = -random_point[0] + nv[i][0]; double coord_vec_y = -random_point[1] + nv[i][1];

        if (fabs(coord_vec_x) < eps && fabs(coord_vec_y) < eps) {
            std::cout << "Point on edge\n";
            return 0;
        }

        vectors.push_back({coord_vec_x, coord_vec_y });
        double angle = vec_angle(vectors[i-1], vectors[i]);

        if (fabs(fabs(angle) - 180.0) < eps) {
            std::cout << "Point on edge\n";
            return 0;
        }

        angles_sum += angle;
    }
    
    angles_sum += vec_angle(vectors[vectors.size()-1], vectors[0]);

    if (fabs(fabs(angles_sum) - 360.0) < eps) {std::cout << "Point in polygon\n";}
    if (fabs(angles_sum) < eps) {std::cout << "Point out polygon\n";}

    return 0;
}

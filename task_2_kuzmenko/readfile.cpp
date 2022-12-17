#include "readfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "parse_arguments.h"

ParseErrors Coords(std::string filename, std::vector<std::vector <double>>& cvector)
{
    double x; double y;
    std::ifstream in(filename); 
    if (!in)
    {
        return ParseErrors::FILE_NOT_EXISTS;
    }
    
    while (!in.eof()) {
            in >> x >> y;  
            if (in.fail())
            {
                return ParseErrors::INCORRECT_FILE;
            }
            cvector.push_back({x, y});   
    }

    return ParseErrors::SUCCESS;
}

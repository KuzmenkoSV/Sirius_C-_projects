#include "parse_arguments.h" 
#include <sstream> 
#include <cstdio> 
#include <iostream>

ParseErrors parse_arguments(int argc, char **argv, double &x, double &y)
{
    if (argc < 4)
    {
        return ParseErrors::INSUFFICIENT_ARGUMENTS;
    }
    if (argc > 4)
    {
        return ParseErrors::TO_MUCH_ARGUMENTS;
    }
    {
        std::istringstream iss(argv[2]);

        iss >> x;

        if (iss.fail())
        {
            return ParseErrors::NOT_A_NUMBER;
        }
    }

    {
        std::istringstream iss(argv[3]);

        iss >> y;
    
        if (iss.fail())
        {
            return ParseErrors::NOT_A_NUMBER;
        }
    }

    return ParseErrors::SUCCESS;
}

std::string get_error_name(ParseErrors err_info)
{
    switch (err_info)
    {
        case ParseErrors::INCORRECT_FILE :
            return "Incorrectly written file";
        case ParseErrors::FILE_NOT_EXISTS:
            return "File not found";
        case ParseErrors::INSUFFICIENT_ARGUMENTS:
            return "Not enough arguments";
        case ParseErrors::TO_MUCH_ARGUMENTS:
            return "To much arguments";
        case ParseErrors::NOT_A_NUMBER:
            return "Can not convert input argument to double";
        case ParseErrors::SUCCESS:
            return "No error";
        default:
            return "Unknown error";
    }
    return "Unknown error"; 
}
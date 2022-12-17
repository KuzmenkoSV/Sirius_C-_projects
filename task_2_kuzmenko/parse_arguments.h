#pragma once 

#include <string> 
enum class ParseErrors 
{
    INCORRECT_FILE = -5,
    FILE_NOT_EXISTS = -4,
    INSUFFICIENT_ARGUMENTS = -3, 
    TO_MUCH_ARGUMENTS = -2,
    NOT_A_NUMBER = -1,
    SUCCESS = 0
};

[[nodiscard]] ParseErrors parse_arguments(int argc, char **argv, double &x, double &y); 

std::string get_error_name(ParseErrors err_info); 

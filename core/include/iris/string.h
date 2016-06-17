#ifndef IRIS_STRING_H
#define IRIS_STRING_H

#include <string>
#include <vector>


namespace iris
{
    std::vector<std::string>& split
    (
        const std::string& string, char delimeter, 
        std::vector<std::string>& elements
    );
    std::vector<std::string> split
    (
        const std::string& string, char delimeter
    );
}


#endif  // IRIS_STRING_H

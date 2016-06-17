#include <iris/string.h>

#include <sstream>


using namespace iris;


std::vector<std::string>& iris::split
(
    const std::string& string, 
    char delimeter, 
    std::vector<std::string>& elements
) 
{
    std::stringstream ss(string);
    std::string item;
    while (std::getline(ss, item, delimeter))
    {
        elements.push_back(item);
    }
    return elements;
}
std::vector<std::string> iris::split
(
    const std::string& string, char delimeter) 
{
    std::vector<std::string> elements;
    split(string, delimeter, elements);
    return elements;
}

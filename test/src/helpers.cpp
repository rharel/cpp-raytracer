#include "helpers.h"

#include <glm/geometric.hpp>

#include <iostream>


using namespace iris;


void print(const Vector3& v)
{
    std::cout << '(' 
              << v.x << ", " << v.y << ", " << v.z 
              << ')' << std::endl;
}
bool is_close(

    const Vector3& a, const Vector3& b,
    const float precision)
{
    return glm::length(a - b) < precision;
}

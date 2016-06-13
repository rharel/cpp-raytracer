#include "helpers.h"

#include <glm/geometric.hpp>

#include <iostream>


using namespace iris;


void print(const Vector2& v)
{
    std::cout << '(' 
              << v.x << ", " << v.y 
              << ')' << std::endl;
}
void print(const Vector3& v)
{
    std::cout << '(' 
              << v.x << ", " << v.y << ", " << v.z 
              << ')' << std::endl;
}
void print(const Vector4& v)
{
    std::cout << '(' 
              << v.x << ", " << v.y << ", " << v.z << ", " << v.w 
              << ')' << std::endl;
}

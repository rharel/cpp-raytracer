#ifndef IRIS_TEST_HELPERS_H
#define IRIS_TEST_HELPERS_H

#include <iris/vector_types.h>

#include <glm/geometric.hpp>


void print(const iris::Vector2& v);
void print(const iris::Vector3& v);
void print(const iris::Vector4& v);

template<typename T>
bool is_close(

    const T& a, const T& b,
    const float precision = 0.001f)
{
    return glm::length(a - b) < precision;
}

#endif  // IRIS_TEST_HELPERS_H

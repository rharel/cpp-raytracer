#ifndef IRIS_TEST_HELPERS_H
#define IRIS_TEST_HELPERS_H

#include <iris/VectorTypes.h>


void print(const iris::Vector3& v);
bool is_close(

    const iris::Vector3& a, const iris::Vector3& b,
    const float precision = 0.00001f);

#endif  // IRIS_TEST_HELPERS_H

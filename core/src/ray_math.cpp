#include <iris/ray_math.h>

#include <glm/geometric.hpp>


using namespace iris;
using glm::dot;
using glm::normalize;


float iris::form_factor(
            
    const Vector3& a, const Vector3& Na,
    const Vector3& b, const Vector3& Nb) 
{
    Vector3 D = b - a;
    Vector3 v = normalize(D);

    return (abs(dot(v, Na)) * abs(dot(v, Nb))) / dot(D, D);
}

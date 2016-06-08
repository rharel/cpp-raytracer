#include <iris/math.h>

#include <cmath>


using namespace iris;


bool iris::solve_quadratic(

    const float a, const float b, const float c,
    float& x0, float& x1)
{
    const float delta = b * b - 4 * a * c;
    if (delta < 0) { return false; }
    else if (delta == 0)
    {
        x0 = x1 = -b / (2.0f * a);
    }
    else 
    {
        const float sqrt_delta = sqrt(delta);
        const float divisor = 2.0f * a;
        x0 = (-b + sqrt_delta) / divisor;
        x1 = (-b - sqrt_delta) / divisor;
    }

    return true; 
}

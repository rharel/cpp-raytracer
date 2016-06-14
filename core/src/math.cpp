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

float iris::gaussian_2d
(
    const float x, const float y,
    const float x0, const float y0,
    const float sigma_x, const float sigma_y,
    const float A
)
{
    /**
     * f(x, y) = A * exp(-a)
     *
     * Where:
     *      a = a_x + a_y
     *      a_x = ((x - x0)^2) / (2 * (s_x)^2)
     *      a_y = ((y - y0)^2) / (2 * (s_y)^2)
     */
    const float a_x = 
    (
        pow(x - x0, 2) / 
        (2 * pow(sigma_x, 2))
    );
    const float a_y = 
    (
        pow(y - y0, 2) / 
        (2 * pow(sigma_y, 2))
    );
    const float a = a_x + a_y;
    return A * exp(-a);
}
float iris::gaussian_2d_isotropic
(
    const float x, const float y,
    const float x0, const float y0,
    const float sigma
)
{
    const float A = 1.0f / (2 * constant::m_pi * pow(sigma, 2));
    return gaussian_2d(x, y, x0, y0, sigma, sigma, A);
}

void iris::to_cartesian
(
    const float theta, const float phi,
    float& x, float& y, float& z
)
{
    x = sin(theta) * cos(phi);
    y = sin(theta) * sin(phi);
    z = cos(theta);
}

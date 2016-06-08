#ifndef IRIS_MATH_H
#define IRIS_MATH_H
/**
 * @file math.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Math utility methods.
 */


namespace iris
{
    namespace constant
    {
        constexpr float m_pi = 3.1415926535897932384f;
        constexpr float m_2_pi = 2.0f * m_pi;
    }

    /**
     * Solves the quadratic equation ax^2 + bx + c = 0
     */
    bool solve_quadratic(
        
        float a, float b, float c,
        float& x0, float& x1);
}


#endif  // IRIS_MATH_H

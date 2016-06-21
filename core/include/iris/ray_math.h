#ifndef IRIS_RAY_MATH_H
#define IRIS_RAY_MATH_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Ray operations.
 */


#include <iris/vector_types.h>


namespace iris
{
    /**
     * @brief   Computes the form factor (also known as G) between two points.
     *
     * @param   a      Point A.
     * @param   Na     Surface normal at A.
     * @param   b      Point B.
     * @param   Nb     Surface normal at B.
     *
     * @returns Form factor G between A and B.
     */
    float form_factor
    (
        const Vector3& a, const Vector3& Na,
        const Vector3& b, const Vector3& Nb
    );
}


#endif  // IRIS_RAY_MATH_H

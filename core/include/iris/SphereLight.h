#ifndef IRIS_SPHERE_LIGHT_H
#define IRIS_SPHERE_LIGHT_H
/**
 * @file SphereLight.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * SphereLight class.
 */


#include <iris/Light.h>


namespace iris
{
    /**
     * Spherical ligth source.
     */
    class SphereLight : public Light
    {
        public:
        /**
         * Creates a white light.
         */
        SphereLight();
        /**
         * Creates a light with given color and intensity.
         */
        SphereLight(const Vector3& color, float intensity);
    };
}


#endif  // IRIS_SPHERE_LIGHT_H

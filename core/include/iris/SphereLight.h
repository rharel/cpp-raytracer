#ifndef IRIS_SPHERE_LIGHT_H
#define IRIS_SPHERE_LIGHT_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * SphereLight class.
 */


#include <iris/Light.h>
#include <iris/vector_types.h>


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

        /**
         * Generates a random point on light's surface.
         *
         * @param[out] position Surface point.
         * @param[out] normal   Normal at point.
         */
        void random_on_surface(Vector3& position, Vector3& normal) const override;
        
        /**
         * Gets light surface area.
         */
        float surface_area() const override;
        /**
         * Gets radius.
         */
        float radius() const;
    };
}


#endif  // IRIS_SPHERE_LIGHT_H

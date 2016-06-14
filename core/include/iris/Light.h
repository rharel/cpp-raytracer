#ifndef IRIS_LIGHT_H
#define IRIS_LIGHT_H
/**
 * @file Light.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Light abstract class.
 */


#include <iris/Object3D.h>


namespace iris
{
    /**
     * The light class is the basis for all lights in the scene.
     */
    class Light : public Object3D
    {
        public:
        /**
         * Creates a white light.
         */
        Light();
        /**
         * Creates a light with given color and intensity.
         */
        Light(const Vector3& color, float intensity);

        /**
         * Generates a random point on light's surface.
         *
         * @param[out] position Surface point.
         * @param[out] normal   Normal at point.
         */
        virtual void random_on_surface(Vector3& position, Vector3& normal) const = 0;
        
        /**
         * Gets light surface area.
         */
        virtual float surface_area() const = 0;
         /**
         * Gets color.
         */
        const Vector3& color() const;
        /**
         * Gets intensity.
         */
        float intensity() const;

        private:
        Vector3 color_;
        float intensity_;
    };
}


#endif  // IRIS_LIGHT_H

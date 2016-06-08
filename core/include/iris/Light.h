#ifndef IRIS_LIGHT_H
#define IRIS_LIGHT_H
/**
 * @file Light.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Light abstract class.
 */


#include <iris/SceneComponent.h>


namespace iris
{
    /**
     * The light class is the basis for all lights in the scene.
     */
    class Light : SceneComponent
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

        const Vector3& color() const;
        float intensity() const;

        private:
        Vector3 color_;
        float intensity_;
    };
}


#endif  // IRIS_LIGHT_H

#ifndef IRIS_RAYTRACER_H
#define IRIS_RAYTRACER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Raytracer abstract class.
 */


#include <iris/Ray.h>
#include <iris/Scene.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * Traces rays through the scene.
     */
    class Raytracer
    {
        public:
        /**
         * Traces a ray through the scene.
         */
        virtual Vector3 trace(Ray ray, const Scene& scene) const = 0;
    };
}


#endif  // IRIS_RAYTRACER_H

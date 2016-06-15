#ifndef IRIS_NAIVE_TRACER_H
#define IRIS_NAIVE_TRACER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * NaiveTracer class.
 */


#include <iris/Ray.h>
#include <iris/Raytracer.h>
#include <iris/Scene.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * Traces rays through the scene. Returns the color of first
     * hit's material.
     */
    class NaiveTracer : public Raytracer
    {
        public:
        /**
         * Creates default tracer.
         */
        NaiveTracer();
        /**
         * Creates tracer with given horizon color.
         *
         * @param horizon Horizon color.
         */
        NaiveTracer(const Vector3& horizon);

        /**
         * Traces a ray through the scene.
         */
        Vector3 trace(Ray ray, const Scene& scene) const override;

        /**
         * Gets horizon color.
         */
        const Vector3& horizon() const;

        private:
        Vector3 horizon_;
    };
}


#endif  // IRIS_NAIVE_TRACER_H

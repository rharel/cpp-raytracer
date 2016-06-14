#ifndef IRIS_PATH_TRACER_H
#define IRIS_PATH_TRACER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * PathTracer class.
 */


#include <iris/Ray.h>
#include <iris/Raytracer.h>
#include <iris/Scene.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * Traces rays through the scene.
     */
    class PathTracer : public Raytracer
    {
        public:
        /**
         * Creates default tracer.
         */
        PathTracer();
        /**
         * Creates tracer with given horizon color.
         *
         * @param horizon Horizon color.
         */
        PathTracer(const Vector3& horizon);
        /**
         * Creates a tracer with given maximum ray
         * bounce limit.
         *
         * @param max_depth Won't trace rays beyond this many bounces.
         *                  If < 0, will trace until ray weight is near
         *                  zero.
         */
        PathTracer(int max_depth);
        /**
         * Creates tracer with given parameters.
         *
         * @param horizon Horizon color.
         * @param max_depth Won't trace rays beyond this many bounces.
         *                  If < 0, will trace until ray weight is near
         *                  zero.
         */
        PathTracer(const Vector3& horizon, int max_depth);

        /**
         * Traces a ray through the scene.
         */
        Vector3 trace(const Ray& ray, const Scene& scene) const override;

        /**
         * Gets horizon color.
         */
        const Vector3& horizon() const;
        /**
         * Gets max_depth.
         */
        int max_depth() const;

        private:
        Vector3 illuminate
        (
            const Scene& scene,
            const Vector3& position,
            const Vector3& normal,
            const Material& material,
            const Vector3& Wi
        ) const;

        Vector3 horizon_;
        int max_depth_;
    };
}


#endif  // IRIS_PATH_TRACER_H

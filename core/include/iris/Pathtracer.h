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
         * @param max_bounce_count
         *      Won't trace rays beyond this many bounces.
         *      If zero, will trace until ray weight is near
         *      zero.
         */
        PathTracer(size_t max_bounce_count);
        /**
         * Creates tracer with given parameters.
         *
         * @param horizon Horizon color.
         * @param max_bounce_count
         *      Won't trace rays beyond this many bounces.
         *      If zero, will trace until ray weight is near
         *      zero.
         */
        PathTracer(const Vector3& horizon, size_t max_bounce_count);

        /**
         * Traces a ray through the scene.
         */
        Vector3 trace(Ray ray, const Scene& scene) const override;

        /**
         * Gets horizon color.
         */
        const Vector3& horizon() const;
        /**
         * Gets max_bounce_count.
         */
        size_t max_bounce_count() const;

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
        size_t max_bounce_count_;
    };
}


#endif  // IRIS_PATH_TRACER_H

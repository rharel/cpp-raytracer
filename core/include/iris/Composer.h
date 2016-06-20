#ifndef IRIS_COMPOSER_H
#define IRIS_COMPOSER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Composer class.
 */


#include <iris/Scene.h>
#include <iris/Camera.h>
#include <iris/Image.h>

#include <iris/Ray.h>
#include <iris/Raytracer.h>
#include <iris/PathTracer.h>

#include <iris/Sampler.h>
#include <iris/NaiveSampler.h>
#include <iris/aggregators.h>

#include <iris/vector_types.h>


namespace iris
{
    /**
     * The composer takes a camera, tracer, and scene, and uses those to
     * render an image.
     */
    class Composer
    {
        public:
        /**
         * Creates default composer.
         */
        Composer
        (
            const Scene& scene, 
            const Camera& camera,
            const Vector2u& image_size
        );
        /**
         * Creates composer with given sampler, tracer, and aggregator.
         */
        Composer
        (
            const Scene& scene, 
            const Camera& camera,
            const Vector2u& image_size,
            Sampler& sampler, 
            const Raytracer& tracer,
            const Aggregator& aggregator
        );

        /**
         * Renders image.
         */
        void render();
        /*
         * Renders to selected range of pixels.
         *
         * @param offset Range start.
         * @param count  Range size (zero implies entire image).
         *
         * @returns Range end (exclusive).
         */
        Vector2u render(const Vector2u& offset, size_t count);

        /**
         * Gets image.
         */
        const Image& image() const;

        private:
        static NaiveSampler default_sampler;
        static UniformAggregator default_aggregator;
        static PathTracer default_tracer;

        /**
         * Renders a pixel.
         */
        void render_pixel(size_t x, size_t y);
        /**
         * Makes a ray that passes through given pixel.
         */
        Ray ray_through(float x, float y) const;

        const Scene* scene_;
        const Camera* camera_;
        Sampler* sampler_;
        const Raytracer* tracer_;
        const Aggregator* aggregator_;
        Image image_;
    };
}


#endif  // IRIS_COMPOSER_H

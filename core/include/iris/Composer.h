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
#include <iris/Pathtracer.h>

#include <iris/Sampler.h>
#include <iris/NaiveSampler.h>
#include <iris/sample_aggregators.h>

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
            size_t image_width, size_t image_height,
            const Scene& scene, const Camera& camera
        );
        /**
         * Creates composer with given sampler/tracer.
         */
        Composer
        (
            size_t image_width, size_t image_height,
            const Scene& scene, const Camera& camera,
            Sampler& sampler, const Aggregator& aggregator,
            const Raytracer& tracer
        );

        /*
         * Renders a traced image.
         */
        void render();

        /**
         * Gets image.
         */
        const Image& image() const;

        private:
        static NaiveSampler default_sampler;
        static UniformAggregator default_aggregator;
        static Pathtracer default_tracer;

        /**
         * Renders a pixel.
         */
        void render_pixel(size_t x, size_t y);
        /**
         * Makes a ray that passes through given pixel.
         */
        Ray ray_through(float x, float y) const;

        Image image_;
        Sampler* sampler_;
        const Aggregator* aggregator_;

        const Scene* scene_;
        const Camera* camera_;
        const Raytracer* tracer_;
    };
}


#endif  // IRIS_COMPOSER_H

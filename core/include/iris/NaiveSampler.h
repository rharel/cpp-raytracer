#ifndef IRIS_NAIVE_SAMPLER_H
#define IRIS_NAIVE_SAMPLER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * NaiveSampler class.
 */


#include <iris/Sampler.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * The naive sampler always select pixel centers.
     */
    class NaiveSampler : public Sampler
    {
        public:
        /**
         * Resets sampler state.
         */
        void reset();
        /**
         * Checks if there are more samples to be output.
         */
        bool has_next() const;
        /**
         * Yields the next sample in pixel-normalized coordinates.
         */
        Vector2 next();
        /**
         * Processses the traced ray color for the last output sample.
         */
        void report(const Vector3& color);

        private:
        bool has_next_ = true;
    };
}


#endif  // IRIS_NAIVE_SAMPLER_H

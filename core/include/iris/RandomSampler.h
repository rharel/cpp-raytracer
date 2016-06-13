#ifndef IRIS_RANDOM_SAMPLER_H
#define IRIS_RANDOM_SAMPLER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * RandomSampler class.
 */


#include <iris/Sampler.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * The random sampler samples the pixel area randomly.
     */
    class RandomSampler : public Sampler
    {
        public:
        /**
         * Creates a default sampler (1 sample per pixel).
         */
        RandomSampler();
        /**
         * Creates a sampler for given amount of samples per pixel.
         *
         * @param count Number of samples per pixel.
         */
        RandomSampler(size_t count);

        /**
         * Resets sampler state.
         */
        void reset() override;
        /**
         * Checks if there are more samples to be output.
         */
        bool has_next() const override;
        /**
         * Yields the next sample in pixel-normalized coordinates.
         */
        Vector2 next() override;
        /**
         * Processses the traced ray color for the last output sample.
         */
        void report(const Vector3& color) override;

        private:
        size_t sample_count_;
        size_t sample_index_ = 0;
    };
}


#endif  // IRIS_RANDOM_SAMPLER_H

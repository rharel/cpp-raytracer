#ifndef IRIS_JITTER_SAMPLER_H
#define IRIS_JITTER_SAMPLER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * JitterSampler abstract class.
 */


#include <iris/Sampler.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * Subdivides the pixel into cells and samples randomly 
     * within each one.
     */
    class JitterSampler : public Sampler
    {
        public:
        /**
         * Creates sampler of 1st degree (equivalent to RandomSampler).
         */
        JitterSampler();
        /**
         * Creates sampler of nth degree.
         *
         * @param degree Degree of subdivision.
         */
        JitterSampler(size_t degree);

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

        /**
         * Gets degree of subdivision.
         */
        size_t degree() const;
        /**
         * Gets number of samples per iteration.
         */
        size_t sample_count() const;
        
        private:
        size_t degree_;
        Vector2u cell_ = Vector2u(0, 0);
    };
}


#endif  // IRIS_JITTER_SAMPLER_H

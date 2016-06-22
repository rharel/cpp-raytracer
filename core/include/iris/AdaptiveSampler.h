#ifndef IRIS_ADAPTIVE_SAMPLER_H
#define IRIS_ADAPTIVE_SAMPLER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * AdaptiveSampler abstract class.
 */


#include <iris/Sampler.h>
#include <iris/vector_types.h>

#include <vector>


namespace iris
{
    /**
     * Uses any sampler until pixel variance is smaller than a specified amount.
     */
    class AdaptiveSampler : public Sampler
    {
        public:
        /**
         * Creates sampler with given precision.
         */
        AdaptiveSampler(Sampler& sampler, float precision = 1.0f / 255.0f);

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
         * Gets inner sampler.
         */
        const Sampler& sampler() const;
        /**
         * Gets precision.
         */
        float precision() const;

        private:
        Sampler* sampler_;

        Vector3 color_sum_ = Vector3(0);
        size_t color_count_ = 0;
        Vector3 average_ = Vector3(0);
        
        float precision_;
        float current_precision_ = 1.0f;
    };
}


#endif  // IRIS_ADAPTIVE_SAMPLER_H

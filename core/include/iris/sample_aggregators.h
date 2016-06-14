#ifndef IRIS_SAMPLE_AGGREGATORS_H
#define IRIS_SAMPLE_AGGREGATORS_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Sample weighing methods.
 */


#include <iris/vector_types.h>


namespace iris
{
    class Aggregator
    {
        public:
        virtual Vector3 operator()
        (
            const Vector3 colors[],
            const Vector2 samples[],
            size_t n
        ) const = 0;
    };

    /**
        * Computes the color average with uniform weights.
        */
    class UniformAggregator : public Aggregator
    {
        public:
        Vector3 operator()
        (
            const Vector3 colors[],
            const Vector2 samples[],
            size_t n
        ) const override;
    };
    /**
     * Computes the color average with gaussien weights 
     * based on distance to pixel center.
     */
    class GaussianAggregator : public Aggregator
    {
        public:
        GaussianAggregator();
        GaussianAggregator(float sigma);

        Vector3 operator()
        (
            const Vector3 colors[],
            const Vector2 samples[],
            size_t n
        ) const override;

        private:
        float sigma_;
    };
}


#endif  // IRIS_SAMPLE_AGGREGATORS_H

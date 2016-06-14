#include <iris/sample_aggregators.h>
#include <iris/math.h>

#include <functional>
#include <vector>


using namespace iris;


// UniformAggregator //

Vector3 UniformAggregator::operator()
(
    const Vector3 colors[], 
    const Vector2[] /* samples */,
    const size_t n
) const
{
    return average<Vector3>(&colors[0], &colors[n]);
}

// GaussianAggregator //

GaussianAggregator::GaussianAggregator()
    : GaussianAggregator(1.0f) {}
GaussianAggregator::GaussianAggregator(const float sigma)
    : sigma_(sigma) {}

Vector3 GaussianAggregator::operator()
(
    const Vector3 colors[],
    const Vector2 samples[],
    const size_t n
) const
{
    std::vector<float> weights(n);
    auto it = weights.begin();
    for (size_t i = 0; i < n; ++i)
    {
        const Vector2 sample = samples[i];
        weights[i] = gaussian_2d_isotropic
        (
            sample.x, sample.y,
            0.5f, 0.5f, sigma_
        );
    }
    return weighted_average<Vector3>
    (
        &colors[0], &colors[n],
        weights.begin()
    );
}

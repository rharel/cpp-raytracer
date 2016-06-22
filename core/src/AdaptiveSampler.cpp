#include <iris/AdaptiveSampler.h>

#include <glm/gtx/component_wise.hpp>


using namespace iris;


AdaptiveSampler::AdaptiveSampler
(
    Sampler& sampler, 
    const float precision
)
    : sampler_(&sampler),
      precision_(precision) {}

void AdaptiveSampler::reset()
{
    sampler_->reset();
    color_sum_ = Vector3(0);
    color_count_ = 0;
    average_ = Vector3(0);
    current_precision_ = 1.0f;
}
bool AdaptiveSampler::has_next() const
{
    return current_precision_ > precision_;
}
Vector2 AdaptiveSampler::next()
{
    if (!sampler_->has_next() && has_next())
    {
        sampler_->reset();
    }
    return sampler_->next();
}
void AdaptiveSampler::report(const Vector3& color) 
{
    sampler_->report(color);
    color_sum_ += color;
    ++ color_count_;

    if (!sampler_->has_next())
    {
        const Vector3 old_average = average_;
        const Vector3 new_average = color_sum_ / static_cast<float>(color_count_);
        const Vector3 delta = glm::abs(new_average - old_average);
        current_precision_ = glm::compMax(delta);
        average_ = new_average;
    }
}

const Sampler& AdaptiveSampler::sampler() const
{
    return *sampler_;
}
float AdaptiveSampler::precision() const
{
    return precision_;
}

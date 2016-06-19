#include <iris/JitterSampler.h>
#include <iris/random.h>


using namespace iris;


JitterSampler::JitterSampler()
    : JitterSampler(1) {}
JitterSampler::JitterSampler(const size_t degree)
    : degree_(degree) {}

void JitterSampler::reset()
{
    cell_ = Vector2u(0, 0);
}
bool JitterSampler::has_next() const
{
    return cell_.y < degree_;
}
Vector2 JitterSampler::next()
{
    const float cell_size = 1.0f / static_cast<float>(degree_);
    
    const Vector2 sample
    (
        static_cast<float>(cell_.x) * cell_size + 
        random::real_in_range(0.0f, cell_size),
        
        static_cast<float>(cell_.y) * cell_size + 
        random::real_in_range(0.0f, cell_size)
    );

    ++ cell_.x;
    if (cell_.x == degree_)
    {
        cell_.x = 0;
        ++ cell_.y;
    }

    return sample;
}
void JitterSampler::report(const Vector3&) {}

size_t JitterSampler::degree() const
{
    return degree_;
}
size_t JitterSampler::sample_count() const
{
    return degree() * degree();
}

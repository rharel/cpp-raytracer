#include <iris/RandomSampler.h>
#include <iris/random.h>


using namespace iris;


RandomSampler::RandomSampler()
    : RandomSampler(1) {}
RandomSampler::RandomSampler(const size_t count)
    : sample_count_(count) {}

void RandomSampler::reset()
{
    sample_index_ = 0;
}
bool RandomSampler::has_next() const
{
    return sample_index_ < sample_count_;
}
Vector2 RandomSampler::next()
{
    ++ sample_index_;
    return Vector2
    (
        random::real_in_range(0.0f, 1.0f),
        random::real_in_range(0.0f, 1.0f)
    );
}
void RandomSampler::report(const Vector3& /* color */) {}

size_t RandomSampler::sample_count() const
{
    return sample_count_;
}

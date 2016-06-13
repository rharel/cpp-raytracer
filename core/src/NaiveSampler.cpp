#include <iris/NaiveSampler.h>


using namespace iris;


void NaiveSampler::reset()
{
    has_next_ = true;
}
bool NaiveSampler::has_next() const
{
    return has_next_;
}
Vector2 NaiveSampler::next()
{
    has_next_ = false;
    return Vector2(0.5f);
}
void NaiveSampler::report(const Vector3& /* color */) {}

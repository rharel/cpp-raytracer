#include <iris/Light.h>


using namespace iris;


Light::Light()
    : Light(Vector3(1.0f), 1.0f) {}
Light::Light(const Vector3& color, const float intensity)
    : color_(color), intensity_(intensity) {}

const Vector3& Light::color() const
{
    return color_;
}
float Light::intensity() const
{
    return intensity_;
}

#include <iris/Light.h>

#include <glm/common.hpp>


using namespace iris;


Light::Light()
    : Light(Vector3(1.0f), 1.0f) {}
Light::Light(const Vector3& color, const float intensity)
    : color_(glm::clamp(color, 0.0f, 1.0f)), 
      intensity_(intensity) {}

const Vector3& Light::color() const
{
    return color_;
}
float Light::intensity() const
{
    return intensity_;
}

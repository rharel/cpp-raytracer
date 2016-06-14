#include <iris/SphereLight.h>
#include <iris/math.h>
#include <iris/random.h>

#include <glm/gtx/component_wise.hpp>


using namespace iris;
using namespace iris::constant;


SphereLight::SphereLight()
    : SphereLight(Vector3(1.0f), 1.0f) {}
SphereLight::SphereLight
(
    const Vector3& color,
    const float intensity
)
    : Light(color, intensity) {}

void SphereLight::random_on_surface
(
    Vector3& position, 
    Vector3& normal
) const
{
    const float r1 = random::real_in_range(0.0f, 1.0f);
    const float r2 = random::real_in_range(0.0f, 1.0f);

    const float theta = m_2_pi * r1;
    const float phi = acos(2 * r2 - 1.0f);

    to_cartesian(theta, phi, normal.x, normal.y, normal.z);
    position = world_translation() + radius() * normal;
}
float SphereLight::surface_area() const
{
    return 4.0f * m_pi * radius() * radius();
}
float SphereLight::radius() const
{
    return glm::compMax(scale());  // TODO: world_scale()
}

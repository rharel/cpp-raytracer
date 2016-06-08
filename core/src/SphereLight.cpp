#include <iris/SphereLight.h>


using namespace iris;


SphereLight::SphereLight()
    : SphereLight(Vector3(1.0f), 1.0f) {}
SphereLight::SphereLight(

    const Vector3& color,
    const float intensity
)
    : Light(color, intensity) {}

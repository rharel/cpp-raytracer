#include <iris/Raycast.h>


using namespace iris;


Raycast::Raycast() 
    : ray_(Vector3(0, 0, 0)) {}
Raycast::Raycast(const Ray& ray)
    : ray_(ray) {}

const Ray& Raycast::ray() const
{
    return ray_;
}

bool Raycast::hit() const
{
    return contact_time() > 0.0f;
}

float Raycast::contact_time() const
{
    return contact_time_;
}
const Vector3& Raycast::contact_normal() const
{
    return contact_normal_;
}
const Material& Raycast::contact_material() const
{
    return *contact_material_;
}
void Raycast::contact(
    
    const float time,
    const Vector3& normal,
    const Material& material)
{
    contact_time_ = time;
    contact_normal_ = normal;
    contact_material_ = &material;
}

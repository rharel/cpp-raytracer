#include <iris/Raycast.h>


using namespace iris;


Raycast::Raycast() 
    : Raycast(Ray(Vector3(0))) {}
Raycast::Raycast(const Ray& ray)
    : ray_(ray) {}

const Ray& Raycast::ray() const
{
    return ray_;
}

bool Raycast::hit() const
{
    return time() > 0.0f;
}
Vector3 Raycast::point() const
{
    return ray().origin() + time() * ray().direction();
}

float Raycast::time() const
{
    return time_;
}
const Vector3& Raycast::normal() const
{
    return normal_;
}
const Vector2& Raycast::uv() const
{
    return uv_;
}
void Raycast::contact(
    
    const float time,
    const Vector3& normal,
    const Vector2& uv)
{
    time_ = time;
    normal_ = normal;
    uv_ = uv;
}

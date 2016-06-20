#include <iris/Raycast.h>


using namespace iris;


Raycast::Raycast() 
    : Raycast(Ray()) {}
Raycast::Raycast(const Ray& ray)
    : ray_(ray) {}

const Ray& Raycast::ray() const
{
    return ray_;
}
Ray& Raycast::ray()
{
    return ray_;
}

bool Raycast::hit() const
{
    return time() > 0.0f;
}
Vector3 Raycast::point() const
{
    return ray_.at(time_);
}

float Raycast::time() const
{
    return time_;
}
const Vector3& Raycast::normal() const
{
    return normal_;
}
float Raycast::u() const
{
    return uv_.x;
}
float Raycast::v() const
{
    return uv_.y;
}
const Vector2& Raycast::uv() const
{
    return uv_;
}
const Material& Raycast::material() const
{
    return *material_;
}
void Raycast::contact
(
    const float time,
    const Vector3& normal,
    const Vector2& uv
)
{
    time_ = time;
    normal_ = normal;
    uv_ = uv;
}
void Raycast::contact(const Material& material)
{
    material_ = &material;
}

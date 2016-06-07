#include <iris/Ray.h>


using namespace iris;


Ray::Ray() 
    : Ray(Vector3(0, 0, 0), Vector3(0, 0, 0)) {}
Ray::Ray(const Vector3& direction)
    : Ray(Vector3(0, 0, 0), direction) {}
Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin_(origin), direction_(direction) {}

bool Ray::is_null() const
{
    return direction_ == Vector3(0, 0, 0);
}

Vector3 Ray::at(const float time) const
{
    return origin() + time * direction();
}

const Vector3& Ray::origin() const
{
    return origin_;
}
const Vector3& Ray::direction() const
{
    return direction_;
}

bool Ray::operator==(const Ray& other) const
{
    return this->origin() == other.origin() &&
           this->direction() == other.direction();
}
bool Ray::operator!=(const Ray& other) const
{
    return !(*this == other);
}

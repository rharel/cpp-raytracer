#include <iris/Ray.h>

#include <glm/geometric.hpp>


using namespace iris;


Ray::Ray() 
    : Ray(Vector3(0, 0, 0)) {}
Ray::Ray(const Vector3& direction)
    : Ray(Vector3(0, 0, 0), direction) {}
Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin_(origin), 
      direction_(direction) 
{
    if (!is_null()) 
    { 
        direction_ = glm::normalize(direction_);
    }
}

bool Ray::is_null() const
{
    return direction_ == Vector3(0, 0, 0);
}

Vector3 Ray::at(const float time) const
{
    return origin_ + time * direction_;
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
    return this->origin_ == other.origin_ &&
           this->direction_ == other.direction_;
}
bool Ray::operator!=(const Ray& other) const
{
    return !(*this == other);
}

#include <iris/Pathtracer.h>

#include <glm/common.hpp>


using namespace iris;
using glm::clamp;


Pathtracer::Pathtracer()
    : Pathtracer(Vector3(0), -1) {}
Pathtracer::Pathtracer(const Vector3& horizon)
    : Pathtracer(horizon, -1) {}
Pathtracer::Pathtracer(const int max_depth)
    : Pathtracer(Vector3(0), max_depth) {}
Pathtracer::Pathtracer(const Vector3& horizon, const int max_depth)
    : horizon_(clamp(horizon, 0.0f, 1.0f)), 
      max_depth_(max_depth) {}

Vector3 Pathtracer::trace(const Ray& ray, const Scene& scene) const
{
    Raycast collision(ray); 
    scene.raycast(collision);

    if (!collision.hit()) { return Vector3(1, 0, 0); }
    return Vector3(0, 1, 0);
}
const Vector3& Pathtracer::horizon() const
{
    return horizon_;
}
int Pathtracer::max_depth() const
{
    return max_depth_;
}

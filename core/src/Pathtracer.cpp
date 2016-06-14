#include <iris/PathTracer.h>

#include <glm/common.hpp>


using namespace iris;
using glm::clamp;


PathTracer::PathTracer()
    : PathTracer(Vector3(0), -1) {}
PathTracer::PathTracer(const Vector3& horizon)
    : PathTracer(horizon, -1) {}
PathTracer::PathTracer(const int max_depth)
    : PathTracer(Vector3(0), max_depth) {}
PathTracer::PathTracer(const Vector3& horizon, const int max_depth)
    : horizon_(clamp(horizon, 0.0f, 1.0f)), 
      max_depth_(max_depth) {}

Vector3 PathTracer::trace(const Ray& ray, const Scene& scene) const
{
    Raycast collision(ray); 
    scene.raycast(collision);

    if (!collision.hit()) { return horizon(); }

    return collision.material().brdf();
}
const Vector3& PathTracer::horizon() const
{
    return horizon_;
}
int PathTracer::max_depth() const
{
    return max_depth_;
}

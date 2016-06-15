#include <iris/NaiveTracer.h>


using namespace iris;


NaiveTracer::NaiveTracer()
    : NaiveTracer(Vector3(0)) {}
NaiveTracer::NaiveTracer(const Vector3& horizon)
    : horizon_(horizon) {}

Vector3 NaiveTracer::trace(const Ray ray, const Scene& scene) const
{
    Raycast collision(ray); 
    scene.raycast(collision);

    if (!collision.hit()) { return horizon(); }
    return collision.material().brdf();
}
const Vector3& NaiveTracer::horizon() const
{
    return horizon_;
}

#include <iris/PlaneGeometry.h>

#include <glm/geometric.hpp>


using namespace iris;


const Vector3 PlaneGeometry::anchor = Vector3(0, 0, 0);
const Vector3 PlaneGeometry::normal = Vector3(0, 1, 0);
const Vector3 PlaneGeometry::U = Vector3(1, 0, 0);
const Vector3 PlaneGeometry::V = Vector3(0, 0, 1);

PlaneGeometry::PlaneGeometry()
    : PlaneGeometry(1.0f, 1.0f) {}
PlaneGeometry::PlaneGeometry(const float su, const float sv)
    : texture_scale_(su, sv) {}

void PlaneGeometry::raycast(Raycast& result) const
{
    using glm::dot;

    const Ray& ray = result.ray();
    const Vector3& O = ray.origin();
    const Vector3& D = ray.direction();
    const Vector3& A = anchor;
    const Vector3& N = normal;

    const float ND = dot(N, D);
    if (ND >= 0.0f) { return; }
    
    const float t = dot(-N, O - A) / ND;
    if (result.hit() && result.time() < t) { return; }

    const Vector3 P = ray.at(t);
    const Vector3 AP = P - A;
    const float u = dot(AP, U) / texture_scale_.x;
    const float v = dot(AP, V) / texture_scale_.y;

    result.contact(t, N, Vector2(u, v));
}

const Vector2& PlaneGeometry::texture_scale() const
{
    return texture_scale_;
}

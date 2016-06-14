#include <iris/math.h>
#include <iris/SphereGeometry.h>

#include <glm/geometric.hpp>

#include <algorithm>


using namespace iris;
using namespace constant;
using glm::dot;
using glm::normalize;


const Vector3 SphereGeometry::center = Vector3(0);
const float SphereGeometry::radius = 1;

SphereGeometry::SphereGeometry()
    : SphereGeometry(1, 1) {}
SphereGeometry::SphereGeometry(const float su, const float sv)
    : texture_scale_(su, sv) {}

void SphereGeometry::raycast(Raycast& result) const
{
    /*************
     * FINDING t *
     *************
     * implicit equation for sphere(C, r): 
     *      (x - C.x)^2 + (y - C.y)^2 + (z - C.z)^2 = r^2
     * with P = (x, y, z):
     *      (P - C)^2 = r^2
     *      (P - C)^2 - r^2 = 0
     * substitute P for ray O + tD:
     *      (O - C + tD)^2 - r^2 = 0
     *      (O - C)^2 + 2(O - C)Dt + (tD)^2 - r^2 = 0
     *      (O - C)^2 + 2(O - C)Dt + (t^2)(D^2) - r^2 = 0
     * rearrange:
     *      (D^2)(t^2) + (2(O - C)D)t + ((O - C)^2 - r^2) = 0
     * which equals:
     *      at^2 + bt + c = 0
     * where:
     *      a = D^2 = 1
     *      b = 2(O - C)D
     *      c = (O - C)^2 - r^2
     * check number of solutions with discriminant:
     *      delta = b^2 - 4ac
     *      delta < 0 -> no solution.
     *      delta = 0 -> one solution t.
     *      delta > 0 -> two solutions {t0, t1}, 
     *                   take min(t0, t1).
     */
    const Ray& ray = result.ray();
    const Vector3& O = ray.origin();
    const Vector3& D = ray.direction();
    const Vector3& C = center;
    const float r = radius;

    const Vector3 CO = O - C;
    
    const float b = 2.0f * dot(CO, D);
    const float c = dot(CO, CO) - r * r;

    float t0, t1;
    if (!solve_quadratic(1.0f, b, c, t0, t1)) { return; }
    if (t0 > t1) { std::swap(t0, t1); }
    
    if (t0 < 0) { t0 = t1; }
    if (t0 < 0) { return; }

    const float t = t0;
    if (result.hit() && result.time() < t) { return; }
    
    // contact normal //
    const Vector3 P = ray.at(t);
    const Vector3 N = normalize(P - C);
    
    // contact material //
    const float theta = acos(P.z / r);  // inclination
    const float phi = atan(P.y / P.x);  // azimuth
    const float u = theta / m_pi / texture_scale().x;
    const float v = phi / m_2_pi / texture_scale().y;

    result.contact(t, N, Vector2(u, v));
}

const Vector2& SphereGeometry::texture_scale() const
{
    return texture_scale_;
}

#include <iris/LambertMaterial.h>
#include <iris/color.h>
#include <iris/math.h>
#include <iris/random.h>

#include <glm/common.hpp>
#include <glm/geometric.hpp>


using namespace iris;
using namespace iris::constant;
using glm::clamp;
using glm::normalize;

LambertMaterial::LambertMaterial()
    : LambertMaterial(Vector3(1.0f)) {}
LambertMaterial::LambertMaterial(const float color)
    : LambertMaterial(Vector3(color)) {}
LambertMaterial::LambertMaterial(const int color)
    : LambertMaterial(color::from_hex(color)) {}
LambertMaterial::LambertMaterial
(
    const float r, 
    const float g, 
    const float b
)
    : LambertMaterial(Vector3(r, g, b)) {}
LambertMaterial::LambertMaterial(const Vector3& color)
    : albedo_(clamp(color, 0.0f, 1.0f)) {}

Vector3 LambertMaterial::brdf() const
{
    return albedo();
}
Vector3 LambertMaterial::brdf(const Vector3&, const Vector3&) const
{
    return albedo() / m_pi;
}

Vector3 LambertMaterial::bounce(const Vector3&, float& pdf) const
{
    const float r1 = random::real_in_range(0.0f, 1.0f);
    const float r2 = random::real_in_range(0.0f, 1.0f);

    const float a = m_2_pi * r1;
    const float b = sqrt(1.0f - r2);

    const float x = cos(a) * b;
    const float y = sin(a) * b;
    const float z = sqrt(r2);

    pdf = z / m_pi;
    return normalize(Vector3(x, y, z));
}

const Vector3& LambertMaterial::albedo() const
{
    return albedo_;
}

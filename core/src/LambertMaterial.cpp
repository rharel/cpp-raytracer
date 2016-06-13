#include <iris/LambertMaterial.h>
#include <iris/math.h>


using namespace iris;
using constant::m_pi;


LambertMaterial::LambertMaterial()
    : LambertMaterial(1.0f) {}
LambertMaterial::LambertMaterial(const float color)
    : LambertMaterial(color, color, color) {}
LambertMaterial::LambertMaterial
(
    const float r, 
    const float g, 
    const float b
)
    : albedo_(r, g, b) {}

Vector3 LambertMaterial::brdf() const
{
    return albedo();
}
Vector3 LambertMaterial::brdf(const Vector3&, const Vector3&) const
{
    return albedo() / m_pi;
}

const Vector3& LambertMaterial::albedo() const
{
    return albedo_;
}

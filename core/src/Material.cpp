#include <iris/Material.h>


using namespace iris;


Vector3 Material::brdf() const
{
    return Vector3(0);
}
Vector3 Material::brdf(const Vector3&, const Vector3&) const
{
    return Vector3(0);
}

bool Material::operator==(const Material& other) const
{
    return this == &other;
}
bool Material::operator!=(const Material& other) const
{
    return !(*this == other);
}

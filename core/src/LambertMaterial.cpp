#include <iris/LambertMaterial.h>


using namespace iris;


LambertMaterial::LambertMaterial()
    : LambertMaterial(Material::null.id(), Vector3(0.8f)) {}
LambertMaterial::LambertMaterial(

    const int id,
    const Vector3& albedo
)
    : Material(id), albedo_(albedo) {}

const Vector3& LambertMaterial::albedo() const
{
    return albedo_;
}

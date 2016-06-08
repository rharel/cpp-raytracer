#include <iris/Material.h>


using namespace iris;


Material Material::null;

Material::Material()
    : Material(-1) {}
Material::Material(const int id)
    : id_(id) {}

int Material::id() const
{
    return id_;
}

bool Material::operator==(const Material& other) const
{
    return this->id() == other.id();
}
bool Material::operator!=(const Material& other) const
{
    return !(*this == other);
}

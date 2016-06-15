#include <iris/Material.h>


using namespace iris;


bool Material::operator==(const Material& other) const
{
    return this == &other;
}
bool Material::operator!=(const Material& other) const
{
    return !(*this == other);
}

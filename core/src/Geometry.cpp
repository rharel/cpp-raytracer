#include <iris/Geometry.h>


using namespace iris;


bool Geometry::operator==(const Geometry& other) const
{
    return this == &other;
}
bool Geometry::operator!=(const Geometry& other) const
{
    return !(*this == other);
}

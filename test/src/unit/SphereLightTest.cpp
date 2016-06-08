#include "../../lib/catch.hpp"

#include <iris/SphereLight.h>


using namespace iris;


TEST_CASE("sphere light", "[light][sphere-light]")
{
    const Vector3 color(0.5f);
    const float intensity = 0.8f;
    const SphereLight a;
    const SphereLight b(color, intensity);

    REQUIRE(a.color() == Vector3(1.0f));
    REQUIRE(a.intensity() == 1.0f);
    REQUIRE(b.color() == color);
    REQUIRE(b.intensity() == intensity);
}

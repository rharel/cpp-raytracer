#include "../../lib/catch.hpp"

#include <iris/Light.h>


using namespace iris;


TEST_CASE("light", "[light]")
{
    const Vector3 color(0.5f);
    const float intensity = 0.8f;
    const Light a;
    const Light b(color, intensity);

    REQUIRE(a.color() == Vector3(1.0f));
    REQUIRE(a.intensity() == 1.0f);
    REQUIRE(b.color() == color);
    REQUIRE(b.intensity() == intensity);
}

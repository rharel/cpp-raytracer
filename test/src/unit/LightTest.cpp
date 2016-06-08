#include "../../lib/catch.hpp"

#include <iris/Light.h>


using namespace iris;


TEST_CASE("light", "[light]")
{
    const Vector3 color(0.5f);
    const float intensity = 0.8f;
    const Light a;
    const Light b(color, intensity);
    const Light c(Vector3(10.0f), intensity);
    const Light d(Vector3(-10.0f), intensity);

    REQUIRE(a.color() == Vector3(1.0f));
    REQUIRE(a.intensity() == 1.0f);
    REQUIRE(b.color() == color);
    REQUIRE(b.intensity() == intensity);
    REQUIRE(c.color() == Vector3(1.0f));
    REQUIRE(d.color() == Vector3(0.0f));
}

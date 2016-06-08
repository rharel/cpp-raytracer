#include "../../lib/catch.hpp"

#include <iris/Texture.h>


using namespace iris;


TEST_CASE("texture", "[texture]")
{
    const Material m1(1), m2(2), m3(3), m4(4), m5(5), m6(6);
    const Texture a;
    const Texture b(1, 2, 3, {&m1, &m2, &m3, &m4, &m5, &m6});

    REQUIRE(a.id() == Texture::null.id());
    REQUIRE(a == Texture::null);
    REQUIRE(a.sample(0.5f, 0.5f) == Material::null);

    REQUIRE(b.id() == 1);
    REQUIRE(b != Texture::null);
    REQUIRE(b.resolution() == Vector2u(2, 3));

    const float dx = 1.0f / 2.0f;
    const float dy = 1.0f / 3.0f;

    SECTION("sampling in [0, 1]")
    {
        REQUIRE(b.sample(0.1f * dx, 0.1f * dy) == m1);
        REQUIRE(b.sample(1.1f * dx, 0.1f * dy) == m2);
        REQUIRE(b.sample(0.1f * dx, 1.1f * dy) == m3);
        REQUIRE(b.sample(1.1f * dx, 1.1f * dy) == m4);
        REQUIRE(b.sample(0.1f * dx, 2.1f * dy) == m5);
        REQUIRE(b.sample(1.1f * dx, 2.1f * dy) == m6);
    }
    SECTION("sampling outside [0, 1]")
    {
        REQUIRE(b.sample(-3 + 0.1f * dx, 3 + 0.1f * dy) == m1);
        REQUIRE(b.sample(-3 + 1.1f * dx, 3 + 0.1f * dy) == m2);
        REQUIRE(b.sample(-3 + 0.1f * dx, 3 + 1.1f * dy) == m3);
        REQUIRE(b.sample(-3 + 1.1f * dx, 3 + 1.1f * dy) == m4);
        REQUIRE(b.sample(-3 + 0.1f * dx, 3 + 2.1f * dy) == m5);
        REQUIRE(b.sample(-3 + 1.1f * dx, 3 + 2.1f * dy) == m6);
    }
}

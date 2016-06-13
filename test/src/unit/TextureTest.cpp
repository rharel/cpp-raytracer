#include "../../lib/catch.hpp"

#include <iris/LambertMaterial.h>
#include <iris/Texture.h>


using namespace iris;


TEST_CASE("texture", "[texture]")
{
    const LambertMaterial m0(0), m1(1), m2(2), m3(3), m4(4), m5(5);
    const Texture a;
    const Texture b(2, 3, {&m0, &m1, &m2, &m3, &m4, &m5});

    REQUIRE(a == a);
    REQUIRE(b == b);
    REQUIRE(a != b);

    REQUIRE(a.resolution() == Vector2u(1, 1));
    REQUIRE(a.sample(0.5f, 0.5f) == Texture::default_material);

    REQUIRE(b.resolution() == Vector2u(2, 3));

    const float dx = 1.0f / static_cast<float>(b.resolution().x);
    const float dy = 1.0f / static_cast<float>(b.resolution().y);

    SECTION("sampling inside [0, 1]")
    {
        REQUIRE(b.sample(0.1f * dx, 0.1f * dy) == m0);
        REQUIRE(b.sample(1.1f * dx, 0.1f * dy) == m1);
        REQUIRE(b.sample(0.1f * dx, 1.1f * dy) == m2);
        REQUIRE(b.sample(1.1f * dx, 1.1f * dy) == m3);
        REQUIRE(b.sample(0.1f * dx, 2.1f * dy) == m4);
        REQUIRE(b.sample(1.1f * dx, 2.1f * dy) == m5);
    }
    SECTION("sampling outside [0, 1]")
    {
        REQUIRE(b.sample(-3 + 0.1f * dx, 3 + 0.1f * dy) == m0);
        REQUIRE(b.sample(-3 + 1.1f * dx, 3 + 0.1f * dy) == m1);
        REQUIRE(b.sample(-3 + 0.1f * dx, 3 + 1.1f * dy) == m2);
        REQUIRE(b.sample(-3 + 1.1f * dx, 3 + 1.1f * dy) == m3);
        REQUIRE(b.sample(-3 + 0.1f * dx, 3 + 2.1f * dy) == m4);
        REQUIRE(b.sample(-3 + 1.1f * dx, 3 + 2.1f * dy) == m5);
    }
}

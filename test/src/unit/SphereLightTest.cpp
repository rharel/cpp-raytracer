#include "../../lib/catch.hpp"

#include <iris/SphereLight.h>
#include <iris/math.h>


using namespace iris;
using namespace iris::constant;

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

    SECTION("random on surface")
    {
        SphereLight c;
        c.translation() = Vector3(1, 2, 3);
        c.scale() = Vector3(2);
        c.update();

        Vector3 p, N;
        c.random_on_surface(p, N);

        REQUIRE(glm::length(p - c.translation()) - c.scale().x < 0.001f);
    }
    SECTION("radius and surface area")
    {
        SphereLight c;
        c.scale() = Vector3(2);
        c.update();

        REQUIRE(c.radius() == 2);
        REQUIRE(c.surface_area() == 4.0f * m_pi * c.radius() * c.radius());
    }
}

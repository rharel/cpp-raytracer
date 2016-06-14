#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/SphereGeometry.h>


using namespace iris;


TEST_CASE("sphere geometry", "[geometry][plane-geometry]")
{
    const Vector2 texture_scale(0.5f, 2.0f);
    const SphereGeometry a;
    const SphereGeometry b(texture_scale.x, texture_scale.y);

    REQUIRE(a.texture_scale() == Vector2(1));
    REQUIRE(b.texture_scale() == texture_scale);

    SECTION("raycast miss")
    {
        const Ray ray(Vector3(0, 2, 0), Vector3(0, 1, 0));
        Raycast result(ray); b.raycast(result);
        REQUIRE(result.time() <= 0);
    }
    SECTION("raycast hit")
    {
        const Vector3 D(-1, 0, 0);
        const Ray ray0(Vector3(2, 0, 0), D);

        Raycast result0(ray0); b.raycast(result0);

        REQUIRE(result0.time() - 1 < 0.0001f);
        REQUIRE(result0.normal() == Vector3(1, 0, 0));
    }
}

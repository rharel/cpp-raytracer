#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/PlaneGeometry.h>


using namespace iris;


TEST_CASE("plane geometry", "[geometry][plane-geometry]")
{
    const Vector2 texture_scale(0.5f, 2.0f);
    const PlaneGeometry a;
    const PlaneGeometry b(texture_scale.x, texture_scale.y);

    REQUIRE(a.texture_scale() == Vector2(1));
    REQUIRE(b.texture_scale() == texture_scale);

    SECTION("raycast miss")
    {
        const Ray ray(Vector3(0, 1, 0), Vector3(0, 1, 0));
        Raycast result(ray); b.raycast(result);
        REQUIRE(result.time() <= 0);
    }
    SECTION("raycast hit")
    {
        const Vector3 Y(0, 1, 0);
        const Ray ray0(Vector3(0.01, 1, 0.01), -Y);
        const Ray ray1(Vector3(0.40, 2,    0), -Y);
        const Ray ray2(Vector3(0,    3, 1.01), -Y);

        Raycast result0(ray0); b.raycast(result0);
        Raycast result1(ray1); b.raycast(result1);
        Raycast result2(ray2); b.raycast(result2);

        REQUIRE(result0.time() == 1);
        REQUIRE(result1.time() == 2);
        REQUIRE(result2.time() == 3);
        REQUIRE(result0.normal() == b.normal);
        REQUIRE(result1.normal() == b.normal);
        REQUIRE(result2.normal() == b.normal);
        REQUIRE(is_close(result0.uv(), Vector2(0.02, 0.005)));
        REQUIRE(is_close(result1.uv(), Vector2(0.80, 0.00)));
        REQUIRE(is_close(result2.uv(), Vector2(0.00, 0.505)));
    }
}

#include "../../lib/catch.hpp"

#include <iris/PlaneSurface.h>


using namespace iris;


TEST_CASE("plane surface", "[surface][plane-surface]")
{
    const Material m0(0), m1(1);
    const Texture texture(1, 2, 2, {&m0, &m1, &m1, &m0});
    const Vector2 texture_tile_size(0.5f, 2.0f);
    const PlaneSurface a;
    const PlaneSurface b(texture, texture_tile_size);

    REQUIRE(a.texture() == Texture::null);
    REQUIRE(b.texture() == texture);
    REQUIRE(b.texture_tile_size() == texture_tile_size);
    REQUIRE(b.anchor() == Vector3(0));
    REQUIRE(b.normal() == Vector3(0, 1, 0));
    REQUIRE(b.U() == Vector3(1, 0, 0));
    REQUIRE(b.V() == Vector3(0, 0, 1));

    SECTION("raycast miss")
    {
        const Ray ray(Vector3(0, 1, 0), Vector3(0, 1, 0));
        Raycast result(ray); b.raycast(result);
        REQUIRE(result.contact_time() <= 0);
    }
    SECTION("raycast hit")
    {
        const Ray ray0(Vector3(0,    1,    0), Vector3(0, -1, 0));
        const Ray ray1(Vector3(0.26, 2,    0), Vector3(0, -1, 0));
        const Ray ray2(Vector3(0,    3, 1.01), Vector3(0, -1, 0));

        Raycast result0(ray0); b.raycast(result0);
        Raycast result1(ray1); b.raycast(result1);
        Raycast result2(ray2); b.raycast(result2);

        REQUIRE(result0.contact_time() == 1);
        REQUIRE(result1.contact_time() == 2);
        REQUIRE(result2.contact_time() == 3);
        REQUIRE(result0.contact_normal() == b.normal());
        REQUIRE(result1.contact_normal() == b.normal());
        REQUIRE(result2.contact_normal() == b.normal());
        REQUIRE(result0.contact_material() == m0);
        REQUIRE(result1.contact_material() == m1);
        REQUIRE(result2.contact_material() == m1);
    }
}

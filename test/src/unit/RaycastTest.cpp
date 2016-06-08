#include "../../lib/catch.hpp"

#include <iris/Raycast.h>


using namespace iris;


TEST_CASE("raycast", "[raycast]")
{
    const Ray ray(Vector3(1, 0, 0));
    const Raycast a;
    const Raycast b(ray);

    REQUIRE(a.ray().is_null());
    REQUIRE(b.ray() == ray);

    REQUIRE(a.contact_time() <= 0);
    REQUIRE(b.contact_time() <= 0);

    SECTION("setters")
    {
        const float t = 1.0f;
        const Vector3 n(0, 1, 0);
        const Material material;
        Raycast c;

        c.contact(t, n, material);

        REQUIRE(c.contact_time() == t);
        REQUIRE(c.contact_normal() == n);
        REQUIRE(c.contact_material() == material);
    }
}

#include "../../lib/catch.hpp"

#include <iris/Raycast.h>
#include <iris/LambertMaterial.h>


using namespace iris;


TEST_CASE("raycast", "[raycast]")
{
    const Ray ray(Vector3(1, 0, 0));
    const Raycast a;
    const Raycast b(ray);

    REQUIRE(a.ray().is_null());
    REQUIRE(a.time() <= 0);
    
    REQUIRE(b.ray() == ray);
    REQUIRE(b.time() <= 0);

    SECTION("setters")
    {
        const float t = 1.0f;
        const Vector3 n(0, 1, 0);
        const Vector2 uv(0.25, 0.75);
        const LambertMaterial m;

        Raycast c(ray);
        
        REQUIRE_FALSE(c.hit());

        c.contact(t, n, uv);
        c.contact(m);

        REQUIRE(c.hit());
        REQUIRE(c.time() == t);
        REQUIRE(c.normal() == n);
        REQUIRE(c.uv() == uv);
        REQUIRE(c.material() == m);
        REQUIRE(c.point() == ray.origin() + t * ray.direction());
    }
}

#include "../../lib/catch.hpp"

#include <iris/Ray.h>


using namespace iris;


TEST_CASE("ray", "[ray]")
{
    const Vector3 origin(1, 0, 0);
    const Vector3 direction(0, 1, 0);

    const Ray a;
    const Ray b(direction);
    const Ray c(origin, direction);

    REQUIRE(a.is_null());

    REQUIRE_FALSE(b.is_null());
    REQUIRE(b.origin() == Vector3(0, 0, 0));
    REQUIRE(b.direction() == direction);
    
    REQUIRE_FALSE(c.is_null());
    REQUIRE(c.origin() == origin);
    REQUIRE(c.direction() == direction);

    SECTION("null ray")
    {
        REQUIRE(Ray(Vector3(0, 0, 0)).is_null());
    }
    SECTION("direction normalized")
    {
        REQUIRE(Ray(Vector3(2, 0, 0)).direction() == 
                Vector3(1, 0, 0));
    }
    SECTION("evaluation")
    {
        REQUIRE(c.at(0) == c.origin());
        REQUIRE(c.at(1) == 
                c.origin() + c.direction());
    }
    SECTION("== and !=")
    {
        REQUIRE(a == a);
        REQUIRE(a != b);
    }
}

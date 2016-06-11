#include "../../lib/catch.hpp"

#include <iris/Material.h>


using namespace iris;


TEST_CASE("material", "[material]")
{
    const Material a;
    const Material b(0);

    REQUIRE(Material::null.id() < 0);
    REQUIRE(a.id() == Material::null.id());
    REQUIRE(a == Material::null);
    REQUIRE(b.id() == 0);
    REQUIRE(b != Material::null);
}

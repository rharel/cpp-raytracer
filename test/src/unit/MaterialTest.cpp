#include "../../lib/catch.hpp"

#include <iris/Material.h>


using namespace iris;


TEST_CASE("material", "[material]")
{
    const Material a;
    const Material b(1);

    REQUIRE(a.id() == Material::null.id());
    REQUIRE(a == Material::null);
    REQUIRE(b.id() == 1);
    REQUIRE(b != Material::null);
}

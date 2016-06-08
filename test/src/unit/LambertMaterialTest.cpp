#include "../../lib/catch.hpp"

#include <iris/LambertMaterial.h>


using namespace iris;


TEST_CASE("lambert material", "[material][lambert-material]")
{
    const Vector3 albedo(0.1f);
    const LambertMaterial a;
    const LambertMaterial b(0, albedo);

    REQUIRE(a == Material::null);
    REQUIRE(b.id() == 0);
    REQUIRE(b.albedo() == albedo);
}

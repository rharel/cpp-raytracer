#include "../../lib/catch.hpp"

#include <iris/LambertMaterial.h>
#include <iris/math.h>


using namespace iris;
using constant::m_pi;


TEST_CASE("lambert material", "[material][lambert-material]")
{
    const Vector3 albedo(0.1f);
    const LambertMaterial a;
    const LambertMaterial b(0, albedo);

    REQUIRE(a == Material::null);
    REQUIRE(b.id() == 0);
    REQUIRE(b.albedo() == albedo);

    const Vector3 Wi(1, 2, 3);
    const Vector3 Wo(4, 5, 6);
    
    REQUIRE(a.brdf() == Vector3(0));
    REQUIRE(a.brdf(Wi, Wo) == Vector3(0));
    REQUIRE(b.brdf() == albedo);
    REQUIRE(b.brdf(Wi, Wo) == albedo / m_pi);
}

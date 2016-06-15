#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/LambertMaterial.h>
#include <iris/math.h>


using namespace iris;
using constant::m_pi;


TEST_CASE("lambert material", "[material][lambert-material]")
{
    const Vector3 albedo(0.5f);
    const LambertMaterial a;
    const LambertMaterial b(albedo.x, albedo.y, albedo.z);
    const LambertMaterial c(albedo.x);
    const LambertMaterial d(0x808080);
    const LambertMaterial e(albedo);

    REQUIRE(a == a);
    REQUIRE(b == b);
    REQUIRE(a != b);

    REQUIRE(a.albedo() == Vector3(1.0f));
    REQUIRE(b.albedo() == albedo);
    REQUIRE(c.albedo() == Vector3(albedo.x));
    REQUIRE(is_close(d.albedo(), albedo, 0.01f));
    REQUIRE(e.albedo() == albedo);

    const Vector3 Wi(1, 2, 3);
    const Vector3 Wo(4, 5, 6);
    
    REQUIRE(a.brdf() == Vector3(1.0f));
    REQUIRE(a.brdf(Wi, Wo) == Vector3(1.0f / m_pi));
    REQUIRE(b.brdf() == albedo);
    REQUIRE(b.brdf(Wi, Wo) == albedo / m_pi);
}

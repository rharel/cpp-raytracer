#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/MirrorMaterial.h>


using namespace iris;


TEST_CASE("mirror material", "[material][mirror-material]")
{
    const MirrorMaterial a;

    const Vector3 Wi = glm::normalize(Vector3(1, 2, 3));
    const Vector3 Wo_y = Vector3(0, 1, 0);
    const Vector3 Wo_reflected = glm::reflect(-Wi, Vector3(0, 1, 0));

    REQUIRE(a.brdf() == Vector3(1.0f));
    REQUIRE(a.brdf(Wi, Wo_y) == Vector3(0.0f));
    REQUIRE(a.brdf(Wi, Wo_reflected) == Vector3(1.0f));
    
    float pdf;
    REQUIRE(is_close(a.bounce(Wi, pdf), Wo_reflected));
    REQUIRE(pdf == 1.0f);
}

#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/Camera.h>


using namespace iris;


TEST_CASE("camera", "[camera]")
{
    const float fov = 1.0f,
                aspect = 2.0f,
                near = 3.0f,
                far = 4.0f;

    const Camera a;
    const Camera b(1.0f, 2.0f, 3.0f, 4.0f);

    REQUIRE(a.fov() > 0);
    REQUIRE(a.aspect() > 0);
    REQUIRE(a.near() > 0);
    REQUIRE(a.far() > 0);
    REQUIRE(a.near() < a.far());

    REQUIRE(b.fov() == fov);
    REQUIRE(b.aspect() == aspect);
    REQUIRE(b.near() == near);
    REQUIRE(b.far() == far);

    SECTION("look at")
    {
        const Vector3 target(0, 0, 0);
        Camera c;
        c.translate(0, 0, 1);
        c.look_at(target);
        c.update();

        REQUIRE(is_close(c.target(), target));
        REQUIRE(is_close(c.forward(), Vector3(0, 0, -1)));
        REQUIRE(is_close(c.right(), Vector3(1, 0, 0)));
        REQUIRE(is_close(c.up(), Vector3(0, 1, 0)));
    }
}

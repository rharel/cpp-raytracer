#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/Camera.h>
#include <iris/math.h>


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

    SECTION("position")
    {
        Camera c;
        c.translate(1, 0, 0);
        c.scale(2, 3, 4);
        c.rotate(constant::m_pi, 0, 0);
        c.update();

        REQUIRE(is_close(c.position(), Vector3(1, 0, 0)));
    }
    SECTION("look at")
    {
        const Vector3 target(0, 0, 0);
        Camera c;

        REQUIRE(c.is_free());

        SECTION("target unspecified")
        {
            c.translate(1, 0, 0);
            c.rotate(0, constant::m_pi, 0);
            c.scale(2, 3, 4);
            c.update();

            REQUIRE(is_close(c.target(), Vector3(1, 0, 1)));
            REQUIRE(is_close(c.forward(), Vector3(0, 0, 1)));
            REQUIRE(is_close(c.right(), Vector3(-1, 0, 0)));
            REQUIRE(is_close(c.up(), Vector3(0, 1, 0)));
        }
        SECTION("target specified")
        {
            c.translate(0, 0, 1);
            c.look_at(target);
            c.update();

            REQUIRE_FALSE(c.is_free());
            REQUIRE(is_close(c.target(), target));
            REQUIRE(is_close(c.forward(), Vector3(0, 0, -1)));
            REQUIRE(is_close(c.right(), Vector3(1, 0, 0)));
            REQUIRE(is_close(c.up(), Vector3(0, 1, 0)));
        }
    }
}

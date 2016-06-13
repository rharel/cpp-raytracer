#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/Camera.h>
#include <iris/math.h>

#include <glm/trigonometric.hpp>


using namespace iris;


TEST_CASE("camera", "[camera]")
{
    const float fov = glm::radians(75.0f),
                aspect = 1.0f,
                near = 0.1f,
                far = 100.0f;

    const Camera a;
    const Camera b(fov, aspect, near, far);

    REQUIRE(a.fov() > 0);
    REQUIRE(a.aspect() > 0);
    REQUIRE(a.near() > 0);
    REQUIRE(a.far() > 0);
    REQUIRE(a.near() < a.far());
    
    REQUIRE(b.fov() == fov);
    REQUIRE(b.aspect() == aspect);
    REQUIRE(b.near() == near);
    REQUIRE(b.far() == far);

    SECTION("projection matrix")
    {
        Vector4 x_near
        (
            b.projection_matrix() * 
            Vector4(0, 0, -near, 1)
        );
        Vector4 x_far
        (
            b.projection_matrix() * 
            Vector4(0, 0, -far, 1)
        );
        x_near /= x_near.w;
        x_far /= x_far.w;

        REQUIRE(x_near == Vector4(0, 0, -1, 1));
        REQUIRE(x_far == Vector4(0, 0, 1, 1));
    }
    SECTION("inverse projection matrix")
    {
        Vector4 x_near
        (
            b.projection_matrix_inverse() * 
            (Vector4(0, 0, -1, 1) * near)
        );
        Vector4 x_far
        (
            b.projection_matrix_inverse() * 
            (Vector4(0, 0, 1, 1) * far)
        );

        REQUIRE(is_close(x_near, Vector4(0, 0, -near, 1)));
        REQUIRE(is_close(x_far, Vector4(0, 0, -far, 1)));
    }
    SECTION("position")
    {
        Camera c;
        c.translation().x = 1;
        c.scale() = Vector3(2, 3, 4);
        c.rotation().x = constant::m_pi;
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
            c.translation().x = 1;
            c.rotation().y = constant::m_pi;
            c.scale() = Vector3(2, 3, 4);
            c.update();

            REQUIRE(is_close(c.target(), Vector3(1, 0, 1)));
            REQUIRE(is_close(c.forward(), Vector3(0, 0, 1)));
            REQUIRE(is_close(c.right(), Vector3(-1, 0, 0)));
            REQUIRE(is_close(c.up(), Vector3(0, 1, 0)));

            const Vector3 x(c.view_matrix() * Vector4(0, 0, -1, 1));
            const Vector3 x_inv(c.view_matrix_inverse() * Vector4(1, 0, 1, 1));

            REQUIRE(is_close(x, Vector3(1, 0, 1)));
            REQUIRE(is_close(x_inv, Vector3(0, 0, -1)));
        }
        SECTION("target specified")
        {
            c.translation().z = -3;
            c.rotation().y = constant::m_pi;
            c.scale() = Vector3(2, 3, 4);
            c.look_at(target);
            c.update();

            REQUIRE_FALSE(c.is_free());
            REQUIRE(is_close(c.target(), target));
            REQUIRE(is_close(c.forward(), Vector3(0, 0, 1)));
            REQUIRE(is_close(c.right(), Vector3(-1, 0, 0)));
            REQUIRE(is_close(c.up(), Vector3(0, 1, 0)));

            const Vector3 x(c.view_matrix() * Vector4(2, 3, -1, 1));
            const Vector3 x_inv(c.view_matrix_inverse() * Vector4(-2, 3, -2, 1));

            REQUIRE(is_close(x, Vector3(-2, 3, -2)));
            REQUIRE(is_close(x_inv, Vector3(2, 3, -1)));
        }
    }
}

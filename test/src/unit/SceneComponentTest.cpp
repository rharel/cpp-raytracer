#include "../../lib/catch.hpp"

#include <iris/math.h>
#include <iris/SceneComponent.h>

#include <glm/geometric.hpp>


using namespace iris;


bool is_close(

    const Vector3& a, const Vector3& b,
    const float precision = 0.00001f)
{
    return glm::length(a - b) < precision;
}

TEST_CASE("scene component", "[scene-component]")
{
    SceneComponent a, b, c;

    REQUIRE_FALSE(a.has_parent());
    REQUIRE_FALSE(a.has_child(a));
    REQUIRE(a.child_count() == 0);

    REQUIRE(a.local_transform() == Matrix4(1.0f));
    REQUIRE(a.global_transform() == Matrix4(1.0f));

    SECTION("child addition")
    {
        REQUIRE_FALSE(a.add_child(a));
        REQUIRE(a.add_child(b));
        REQUIRE_FALSE(a.add_child(b));
        REQUIRE(a.add_child(c));

        REQUIRE(b.has_parent());
        REQUIRE(c.has_parent());
        REQUIRE(a.child_count() == 2);
        REQUIRE(a.has_child(b));
        REQUIRE(a.has_child(c));
        
        const bool is_b_or_c = &a.child(0) == &b || 
                               &a.child(0) == &c;
        REQUIRE(is_b_or_c);
        REQUIRE(&a.child(0) != &a.child(1));

        SECTION("child removal")
        {
            REQUIRE_FALSE(a.remove_child(a));
            REQUIRE(a.remove_child(b));

            REQUIRE_FALSE(b.has_parent());
            REQUIRE_FALSE(a.has_child(b));
            REQUIRE(a.child_count() == 1);
            REQUIRE(&a.child(0) == &c);
        }
    }
    SECTION("transformations")
    {
        REQUIRE(a.add_child(b));
        REQUIRE(b.add_child(c));

        a.translate(1, 0, 0);
        b.rotate(0, constant::m_pi, 0);
        c.scale(1, 1, 2);
        a.update();

        const Matrix4& T = a.local_transform();
        const Matrix4& R = b.local_transform();
        const Matrix4& S = c.local_transform();
        const Matrix4& W = c.global_transform();

        const Vector4 v(1.0f);
        const Vector3 Tv(T * v);
        const Vector3 Rv(R * v);
        const Vector3 Sv(S * v);
        const Vector3 Wv(W * v);

        REQUIRE(is_close(Tv, Vector3(2, 1, 1)));
        REQUIRE(is_close(Rv, Vector3(-1, 1, -1)));
        REQUIRE(is_close(Sv, Vector3(1, 1, 2)));
        REQUIRE(is_close(Wv, Vector3(0, 1, -2)));
    }
}

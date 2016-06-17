#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/math.h>
#include <iris/Object3D.h>
#include <iris/PlaneGeometry.h>


using namespace iris;


TEST_CASE("object3d", "[object3d]")
{
    Object3D a, b, c;

    REQUIRE(a.is_empty());
    REQUIRE_FALSE(a.has_parent());
    REQUIRE_FALSE(a.has_descendant(a));
    REQUIRE(a.child_count() == 0);

    REQUIRE(a.matrix() == Matrix4(1));
    REQUIRE(a.world_matrix() == Matrix4(1));

    SECTION("child addition")
    {
        REQUIRE_FALSE(a.add_child(a));
        REQUIRE(a.add_child(b));
        REQUIRE_FALSE(a.add_child(b));
        REQUIRE(b.add_child(c));
        REQUIRE_FALSE(b.add_child(c));
        REQUIRE_FALSE(b.add_child(a));

        REQUIRE(b.has_parent());
        REQUIRE(c.has_parent());
        REQUIRE(a.child_count() == 1);
        REQUIRE(b.child_count() == 1);
        REQUIRE(c.child_count() == 0);

        REQUIRE(a.has_child(b));
        REQUIRE_FALSE(a.has_child(c));
        REQUIRE(a.has_descendant(c));
        REQUIRE(b.has_child(c));
        REQUIRE(b.has_descendant(c));
        
        REQUIRE(a.child(0) == b);
        REQUIRE(b.child(0) == c);

        SECTION("child removal")
        {
            REQUIRE_FALSE(a.remove_child(a));
            REQUIRE(a.remove_child(b));

            REQUIRE_FALSE(a.has_child(b));
            REQUIRE_FALSE(a.has_descendant(b));
            REQUIRE_FALSE(b.has_parent());
            
            REQUIRE(a.child_count() == 0);
        }
    }
    SECTION("transformations")
    {
        REQUIRE(a.add_child(b));
        REQUIRE(b.add_child(c));

        a.translation().x = 1;
        b.rotation().y = constant::m_pi;
        c.scale() = Vector3(1, 1, 2);
        a.update();

        const Matrix4& T = a.matrix();
        const Matrix4& R = b.matrix();
        const Matrix4& S = c.matrix();
        const Matrix4& W = c.world_matrix();

        const Vector4 v(1);
        const Vector3 Tv(T * v);
        const Vector3 Rv(R * v);
        const Vector3 Sv(S * v);
        const Vector3 Wv(W * v);

        REQUIRE(is_close(Tv, Vector3(2, 1, 1)));
        REQUIRE(is_close(Rv, Vector3(-1, 1, -1)));
        REQUIRE(is_close(Sv, Vector3(1, 1, 2)));
        REQUIRE(is_close(Wv, Vector3(0, 1, -2)));
    }
    SECTION("geometry/texture getters")
    {
        PlaneGeometry plane;
        Texture texture;
        Object3D d(plane, texture);

        REQUIRE(d.geometry() == plane);
        REQUIRE(d.texture() == texture);
    }
}

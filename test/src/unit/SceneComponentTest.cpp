#include "../../lib/catch.hpp"

#include <iris/SceneComponent.h>


using namespace iris;


TEST_CASE("scene component", "[scene-component]")
{
    SceneComponent a, b, c;

    REQUIRE_FALSE(a.has_parent());
    REQUIRE_FALSE(a.has_child(a));
    REQUIRE(a.child_count() == 0);

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
}

#include "../../lib/catch.hpp"

#include <iris/math.h>


using namespace iris;


TEST_CASE("constants", "[math][constants]")
{
    REQUIRE(constant::m_pi == acosf(-1));
    REQUIRE(constant::m_2_pi == 2.0f * constant::m_pi);
}
TEST_CASE("solve quadratic", "[math][solve-quadratic]")
{
    float x0, x1;
    
    SECTION("no solution")
    {
        REQUIRE_FALSE(solve_quadratic(1, 0, 1, x0, x1));
    }
    SECTION("single solution")
    {
        REQUIRE(solve_quadratic(1, 0, 0, x0, x1));
        REQUIRE(x0 == x1);
        REQUIRE(x0 == 0.0f);
    }
    SECTION("dual solution")
    {
        REQUIRE(solve_quadratic(1, 0, -1, x0, x1));
        REQUIRE(x0 ==  1.0f);
        REQUIRE(x1 == -1.0f);
    }
}

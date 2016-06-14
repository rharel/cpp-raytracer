#include "../../lib/catch.hpp"

#include <iris/math.h>
#include <iris/vector_types.h>


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
TEST_CASE("average", "[math][average]")
{
    float reals[3] { 1.0f, 2.0f, 3.0f };
    REQUIRE(average<float>(&reals[0], &reals[3]) == 2.0f);

    Vector3 vectors[3] 
    { 
        Vector3(1, 2, 3),
        Vector3(3, 1, 2),
        Vector3(2, 3, 1)
    };
    const Vector3 avg = average<Vector3>(&vectors[0], &vectors[3]);
    REQUIRE(avg == Vector3(2));
}
TEST_CASE("weighted average", "[math][average-weighted]")
{
    const float reals[3] { 1.0f, 2.0f, 3.0f };
    const float weights[3] { 1.0f, 2.0f, 3.0f };
    REQUIRE(weighted_average<float>
    (
        &reals[0], &reals[3], 
        &weights[0]
    ) == 14.0f / 6.0f);

    Vector3 vectors[3] 
    { 
        Vector3(1, 2, 3),
        Vector3(3, 1, 2),
        Vector3(2, 3, 1)
    };
    const Vector3 avg = weighted_average<Vector3>
    (
        &vectors[0], &vectors[3], 
        &weights[0]
    );
    const Vector3 expected
    (
        13.0f / 6.0f, 
        13.0f / 6.0f, 
        10.0f / 6.0f
    );
    REQUIRE(avg == expected);
}

TEST_CASE("gaussian-2d", "[math][gaussian][gaussian-2d]")
{
    const float x = 0.01f , y = 0.02f, 
                x0 = 3, y0 = 4,
                sigma_x = 1.1f, sigma_y = 2.1f,
                A = 0.5f;
    const float expected = 0.002063468f;
    
    REQUIRE(gaussian_2d(x, y, x0, y0, sigma_x, sigma_y, A) - 
            expected < 0.000001f);
}
TEST_CASE("gaussian-2d-isotropic", "[math][gaussian][gaussian-2d-isotropic]")
{
    const float x = 0.01f , y = 0.02f, 
                x0 = 3, y0 = 4,
                sigma = 1.1f,
                A = 1 / (constant::m_2_pi * sigma);
    const float expected = 0.000005167801f;
    
    REQUIRE(gaussian_2d_isotropic(x, y, x0, y0, sigma) - 
            expected < 0.000001f);
}

#include "../../lib/catch.hpp"


#include <iris/Image.h>


using namespace iris;


TEST_CASE("image", "[image]")
{
    const size_t w = 2, h = 3;
    Image a;
    Image b(0, h);
    Image c(w, 0);
    Image d(w, h);

    REQUIRE(a.width() == 0);
    REQUIRE(a.height() == 0);
    REQUIRE(a.is_empty());
    REQUIRE(a.size() == 0);

    REQUIRE(b.width() == 0);
    REQUIRE(b.height() == 0);
    REQUIRE(b.is_empty());
    REQUIRE(b.size() == 0);

    REQUIRE(c.width() == 0);
    REQUIRE(c.height() == 0);
    REQUIRE(c.is_empty());
    REQUIRE(c.size() == 0);

    REQUIRE(d.width() == w);
    REQUIRE(d.height() == h);
    REQUIRE_FALSE(d.is_empty());
    REQUIRE(d.size() == w * h);

    SECTION("get/set pixels")
    {
        const size_t x = 1, y = 2;

        SECTION("red")
        {
            const Vector3 red(2, -3, -4);
            d.color_pixel(x, y, red);
            REQUIRE(d.pixel(x, y) == Vector3(1, 0, 0));
        }
        SECTION("green")
        {
            const Vector3 green(-3, 2, -4);
            d.color_pixel(x, y, green);
            REQUIRE(d.pixel(x, y) == Vector3(0, 1, 0));
            
        }
        SECTION("blue")
        {
            const Vector3 blue(-3, -4, 2);
            d.color_pixel(x, y, blue);
            REQUIRE(d.pixel(x, y) == Vector3(0, 0, 1));
        }
    }
}

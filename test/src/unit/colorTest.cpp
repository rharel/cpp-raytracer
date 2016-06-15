#include "../../lib/catch.hpp"

#include <iris/color.h>


using namespace iris;
using namespace iris::color;


TEST_CASE("color", "[color][hex]")
{
    REQUIRE(hex(0xFF0000) == Vector3(1, 0, 0));
    REQUIRE(hex(0x00FF00) == Vector3(0, 1, 0));
    REQUIRE(hex(0x0000FF) == Vector3(0, 0, 1));
}

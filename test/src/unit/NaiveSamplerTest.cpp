#include "../../lib/catch.hpp"

#include <iris/NaiveSampler.h>


using namespace iris;


TEST_CASE("naive sampler", "[sampler][naive-sampler]")
{
    NaiveSampler a;

    REQUIRE(a.has_next());
    REQUIRE(a.next() == Vector2(0.5f));
    REQUIRE_FALSE(a.has_next());

    a.reset();

    REQUIRE(a.has_next());
    REQUIRE(a.next() == Vector2(0.5f));
    REQUIRE_FALSE(a.has_next());
}

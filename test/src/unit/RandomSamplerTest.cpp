#include "../../lib/catch.hpp"

#include <iris/RandomSampler.h>

#include <glm/vector_relational.hpp>


using namespace iris;
using glm::all;
using glm::lessThanEqual;


TEST_CASE("random sampler", "[sampler][random-sampler]")
{
    const size_t count = 3;
    RandomSampler a;
    RandomSampler b(count);

    SECTION("default ctor")
    {
        REQUIRE(a.has_next());

        const Vector2 sample = a.next();
        REQUIRE(all(lessThanEqual(Vector2(0), sample)));
        REQUIRE(all(lessThanEqual(sample, Vector2(1))));

        REQUIRE_FALSE(a.has_next());
        a.reset();
        REQUIRE(a.has_next());
    }
    SECTION("count ctor")
    {
        for (size_t i = 0; i < count; ++i)
        {
            REQUIRE(b.has_next());
            
            const Vector2 sample = b.next();
            
            REQUIRE(all(lessThanEqual(Vector2(0), sample)));
            REQUIRE(all(lessThanEqual(sample, Vector2(1))));
        }
       
        REQUIRE_FALSE(b.has_next());
        b.reset();
        REQUIRE(b.has_next());
    }
}

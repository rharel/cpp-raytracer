#include "../../lib/catch.hpp"

#include <iris/JitterSampler.h>

#include <glm/vector_relational.hpp>


using namespace iris;
using glm::all;
using glm::lessThanEqual;


TEST_CASE("jitter sampler", "[sampler][jitter-sampler]")
{
    JitterSampler a(2);
    Vector2 samples[4];

    REQUIRE(a.degree() == 2);
    REQUIRE(a.sample_count() == 4);

    REQUIRE(a.has_next());
    samples[0] = a.next();
    REQUIRE(a.has_next());
    samples[1] = a.next();
    REQUIRE(a.has_next());
    samples[2] = a.next();
    REQUIRE(a.has_next());
    samples[3] = a.next();
    REQUIRE_FALSE(a.has_next());

    REQUIRE(all(lessThanEqual(Vector2(0, 0), samples[0])));
    REQUIRE(all(lessThanEqual(samples[0], Vector2(0.5f, 0.5f))));
    REQUIRE(all(lessThanEqual(Vector2(0.5f, 0), samples[1])));
    REQUIRE(all(lessThanEqual(samples[1], Vector2(1.0f, 0.5f))));
    REQUIRE(all(lessThanEqual(Vector2(0, 0.5f), samples[2])));
    REQUIRE(all(lessThanEqual(samples[2], Vector2(0.5f, 1.0f))));
    REQUIRE(all(lessThanEqual(Vector2(0.5f, 0.5f), samples[3])));
    REQUIRE(all(lessThanEqual(samples[3], Vector2(1.0f, 1.0f))));

    a.reset();
    REQUIRE(a.has_next());
}

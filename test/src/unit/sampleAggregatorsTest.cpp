#include "../../lib/catch.hpp"

#include <iris/sample_aggregators.h>

#include <vector>


using namespace iris;


TEST_CASE("uniform aggregator", "[aggregate][uniform-aggregate]")
{
    std::vector<Vector3> colors
    { 
        Vector3(1, 1, 0), 
        Vector3(0, 1, 1)
    };
    std::vector<Vector2> samples(colors.size());

    REQUIRE(aggregate::uniform(colors, samples) == 
            Vector3(0.5f, 1, 0.5f));
}

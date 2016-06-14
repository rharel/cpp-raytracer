#include "../../lib/catch.hpp"

#include <iris/aggregators.h>

#include <vector>


using namespace iris;


TEST_CASE("uniform aggregator", "[aggregator][uniform-aggregate]")
{
    std::vector<Vector3> colors
    { 
        Vector3(1, 1, 0), 
        Vector3(0, 1, 1)
    };
    std::vector<Vector2> samples(colors.size());
    UniformAggregator a;
    REQUIRE(a(&colors[0], &samples[0], colors.size()) == 
            Vector3(0.5f, 1, 0.5f));
}

#include "../../lib/catch.hpp"

#include <iris/Surface.h>


using namespace iris;


class MockSurface : public Surface 
{
    public:
    MockSurface() : Surface() {}
    MockSurface(const Texture& texture)
        : Surface(texture) {}

    void raycast(Raycast&) const override {}
};

TEST_CASE("surface", "[surface]")
{
    const Texture texture(1, 0, 0, {});

    const MockSurface a;
    const MockSurface b(texture);

    REQUIRE(a.texture() == Texture::null);
    REQUIRE(b.texture() == texture);
}

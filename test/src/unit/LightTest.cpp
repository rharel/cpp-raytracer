#include "../../lib/catch.hpp"

#include <iris/Light.h>


using namespace iris;


class MockLight : public Light
{
    public:
    MockLight() 
        : Light() {}
    MockLight(const Vector3& color, const float intensity)
        : Light(color, intensity) {}
    void random_on_surface(Vector3&, Vector3&) const override {}
    float surface_area() const override { return 1.0f; }
};
TEST_CASE("light", "[light]")
{
    const Vector3 color(0.5f);
    const float intensity = 0.8f;
    const MockLight a;
    const MockLight b(color, intensity);
    const MockLight c(Vector3(10.0f), intensity);
    const MockLight d(Vector3(-10.0f), intensity);

    REQUIRE(a.color() == Vector3(1.0f));
    REQUIRE(a.intensity() == 1.0f);
    REQUIRE(b.color() == color);
    REQUIRE(b.intensity() == intensity);
    REQUIRE(c.color() == Vector3(1.0f));
    REQUIRE(d.color() == Vector3(0.0f));
}

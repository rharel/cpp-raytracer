#include <iris/Texture.h>

#include <algorithm>


using namespace iris;


const LambertMaterial Texture::default_material;

Texture::Texture()
    : Texture(Texture::default_material) {}
Texture::Texture(const Material& material)
    : Texture(1, 1, {&material}) {}
Texture::Texture
(
    const size_t width, const size_t height,
    std::initializer_list<const Material*> pattern
)
    : resolution_(width, height),
      pattern_(pattern.begin(), pattern.end()) {}
Texture::Texture
(
    const size_t width, const size_t height,
    const Material** pattern
)
    : resolution_(width, height),
      pattern_(&pattern[0], &pattern[width * height]) {}

const Material& Texture::sample(float u, float v) const
{
    const size_t w = resolution_.x;
    const size_t h = resolution_.y;
    
    if (w == 0 || h == 0)
    {
        return Texture::default_material;
    }
    
    const float u_mod_1 = abs(fmod(u, 1.0f));
    const float v_mod_1 = abs(fmod(v, 1.0f));
    u = u < 0 ? 1 - u_mod_1 : u_mod_1;
    v = v < 0 ? 1 - v_mod_1 : v_mod_1;

    const float dx = 1.0f / static_cast<float>(w);
    const float dy = 1.0f / static_cast<float>(h);
    size_t i = static_cast<size_t>(floor(u / dx));
    size_t j = static_cast<size_t>(floor(v / dy));
    if (i == w) { i = 0; }
    if (j == h) { j = 0; }

    return *pattern_.at(j * w + i);
}

const Vector2u& Texture::resolution() const
{
    return resolution_;
}

bool Texture::operator==(const Texture& other) const
{
    return this == &other;
}
bool Texture::operator!=(const Texture& other) const
{
    return !(*this == other);
}

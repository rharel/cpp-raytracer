#include <iris/LambertMaterial.h>
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

const Material& Texture::sample(float u, float v) const
{
    if (resolution().x == 0 || 
        resolution().y == 0)
    {
        return Texture::default_material;
    }
    
    const float u_mod_1 = abs(fmod(u, 1.0f));
    const float v_mod_1 = abs(fmod(v, 1.0f));
    u = u < 0 ? 1 - u_mod_1 : u_mod_1;
    v = v < 0 ? 1 - v_mod_1 : v_mod_1;

    const float dx = 1.0f / static_cast<float>(resolution().x);
    const float dy = 1.0f / static_cast<float>(resolution().y);
    size_t i = static_cast<size_t>(floor(u / dx));
    size_t j = static_cast<size_t>(floor(v / dy));
    if (i == resolution().x) { i = 0; }
    if (j == resolution().y) { j = 0; }

    return *pattern_.at(j * resolution().x + i);
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

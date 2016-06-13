#include <iris/LambertMaterial.h>
#include <iris/Texture.h>


using namespace iris;


const Material Texture::default_material = LambertMaterial();

Texture::Texture()
    : Texture(1, 1, {&Texture::default_material}) {}
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
    const size_t i = static_cast<size_t>(floor(u / dx));
    const size_t j = static_cast<size_t>(floor(v / dy));
    
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

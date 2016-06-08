#include <iris/Texture.h>


using namespace iris;


const Texture Texture::null;

Texture::Texture()
    : Texture(-1, 0, 0, {&Material::null}) {}
Texture::Texture(

    const int id,
    const size_t x, const size_t y,
    std::initializer_list<const Material*> data
)
    : id_(id), 
      resolution_(x, y),
      data_(data.begin(), data.end()) {}

const Material& Texture::sample(float u, float v) const
{
    if (*this == Texture::null || 
        resolution().x == 0 || resolution().y == 0)
    {
        return Material::null;
    }
    
    const float umod1 = abs(fmod(u, 1.0f));
    const float vmod1 = abs(fmod(v, 1.0f));
    u = u < 0 ? 1.0f - umod1 : umod1;
    v = v < 0 ? 1.0f - vmod1 : vmod1;
    const float dx = 1.0f / static_cast<float>(resolution().x);
    const float dy = 1.0f / static_cast<float>(resolution().y);
    const size_t i = static_cast<size_t>(floor(u / dx));
    const size_t j = static_cast<size_t>(floor(v / dy));
    
    return *data_.at(j * resolution().x + i);
}

int Texture::id() const
{
    return id_;
}
const Vector2u& Texture::resolution() const
{
    return resolution_;
}

bool Texture::operator==(const Texture& other) const
{
    return this->id() == other.id();
}
bool Texture::operator!=(const Texture& other) const
{
    return !(*this == other);
}

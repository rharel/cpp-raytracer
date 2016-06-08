#include <iris/Surface.h>


using namespace iris;


Surface::Surface()
    : Surface(Texture::null) {}
Surface::Surface(const Texture& texture)
    : texture_(&texture) {}

const Texture& Surface::texture() const
{
    return *texture_;
}

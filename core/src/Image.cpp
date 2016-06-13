#include <iris/Image.h>

#include <glm/common.hpp>


using namespace iris;


Image::Image()
    : Image(0, 0) {}
Image::Image(const size_t width, const size_t height)
    : data_(height, std::vector<Vector3>(width)) {}

bool Image::is_empty() const
{
    return width() == 0 ||  
           height() == 0;
}

const Vector3& Image::pixel(const size_t x, const size_t y) const
{
    return data_.at(y).at(x);
}
void Image::pixel
(
    const size_t x, const size_t y,
    const Vector3& color
)
{
    data_.at(y).at(x) = glm::clamp(color, 0.0f, 1.0f);
}

size_t Image::width() const
{
    if (height() == 0) { return 0; }
    else { return data_.at(0).size(); }
}
size_t Image::height() const
{
    return data_.size();
}
size_t Image::size() const
{
    return width() * height();
}

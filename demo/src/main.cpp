#include <iris/iris.h>

#include "../lib/FreeImagePlus.h"

#include <glm/trigonometric.hpp>

#include <chrono>
#include <iostream>


using namespace iris;
using namespace iris::constant;


RGBQUAD to_24bit(const Vector3& source)
{
    RGBQUAD result;

    result.rgbRed   = static_cast<BYTE>(source.x * 255);
    result.rgbGreen = static_cast<BYTE>(source.y * 255);
    result.rgbBlue  = static_cast<BYTE>(source.z * 255);
    
    return result;
}
void save(const Image& image, const std::string& path)
{
    fipImage img
    (
        FIT_BITMAP, 
        image.width(), image.height(), 
        24
    );
    for (size_t x = 0; x < image.width(); ++x)
    {
        for (size_t y = 0; y < image.height(); ++y)
        {
            RGBQUAD color = to_24bit(image.pixel(x, y));
            img.setPixelColor(x, y, &color);
        }
    }
    if (!img.save(path.c_str()))
    {
        std::cout << "Error saving image!" << std::endl;
    }
}

void main()
{
    const char* config_path = "../config/checkered_sphere.xml";
    XMLConfigurationLoader reader;
    Configuration config = reader.load_from_path(config_path);
    std::cout << reader.status_message() << std::endl;

    UniformAggregator aggregator;
    Composer composer
    (
        *config.scene, config.camera, config.image_size,
        *config.sampler, *config.tracer, aggregator 
    );
    auto begin = std::chrono::high_resolution_clock::now();
    const Vector2u last
    (
        composer.image().width(), 
        composer.image().height()
    );
    Vector2u offset(0, 0);
    const size_t n = 512; static_cast<size_t>(0.01f * composer.image().size());
    size_t k = 0;
    while (offset.y < last.y)
    {
        offset = composer.render(offset, n);
        k += n;
        const int pct = static_cast<int>(round
        (
            100.0f * 
            static_cast<float>(k) / 
            static_cast<float>(composer.image().size())
        ));
        std::cout << pct << "%" << std::endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "Time: "
              << std::chrono::duration_cast
                 <
                    std::chrono::milliseconds
                 >
                (end - begin).count() 
              << " ms" << std::endl;
    
    save(composer.image(), config.image_path);
}

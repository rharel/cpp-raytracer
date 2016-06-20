#include <iris/iris.h>

#include <glm/trigonometric.hpp>

#include "../lib/FreeImagePlus.h"

#include <chrono>
#include <iostream>


using namespace iris;
using namespace iris::constant;


const size_t IMAGE_WIDTH = 512;
const size_t IMAGE_HEIGHT = 512;

const char* PATH_OUTPUT = "../img/demo.bmp";

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
    const char* config_path = "../config/checkered_plane.xml";
    XMLSceneReader reader;
    Configuration config = reader.read_from_path(config_path);
    std::cout << reader.status_message() << std::endl;

    UniformAggregator aggregator;
    Composer composer
    (
        config.image_size.x, config.image_size.y, 
        *config.scene, config.camera, 
        *config.sampler, aggregator, 
        *config.tracer
    );
    auto begin = std::chrono::high_resolution_clock::now();
    composer.render();
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

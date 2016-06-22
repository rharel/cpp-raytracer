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
BOOL save(const Image& image, const std::string& path)
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
    return img.save(path.c_str());
}

void main()
{
    const char* config_path = "../config/three_lambertian_spheres.xml";
    XMLConfigurationLoader reader;

    std::cout << "Loading configuration: " << config_path << std::endl;
    Configuration config = reader.load_from_path(config_path);
    if (reader.status() != ConfigurationLoader::Status::Success)
    {
        std::cout << "ERROR: " << reader.status_message() << std::endl;
        return;
    }

    AdaptiveSampler adaptive_sampler(*config.sampler, config.sampler_precision);
    Sampler& sampler = config.sampler_precision > 0 ? adaptive_sampler : *config.sampler;
    UniformAggregator aggregator;
    Composer composer
    (
        *config.scene, config.camera, config.image_size,
        sampler, *config.tracer, aggregator 
    );
    
    const size_t h = composer.image().height();
    const size_t image_size = composer.image().size();
    const size_t render_batch_size = static_cast<size_t>(0.01f * image_size);
    Vector2u offset(0, 0);
    size_t rendered_count = 0;

    std::cout << "Rendering..." << std::endl;

    auto begin = std::chrono::high_resolution_clock::now();
    while (offset.y < h)
    {
        offset = composer.render(offset, render_batch_size);
        rendered_count += render_batch_size;
        const int pct = static_cast<int>(round
        (
            100.0f * 
            static_cast<float>(rendered_count) / 
            static_cast<float>(image_size)
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

    std::cout << "Saving to: " << config.image_path << std::endl;
    if (!save(composer.image(), config.image_path))
    {
        std::cout << "ERROR: could not save image." << std::endl;
    }
}

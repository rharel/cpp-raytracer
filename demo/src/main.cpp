#include <iris/iris.h>

#include <glm/trigonometric.hpp>

#include "../lib/FreeImagePlus.h"

#include <chrono>
#include <iostream>


using namespace iris;


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
void save(const Image& image)
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
    img.save(PATH_OUTPUT);
}

void main()
{
    LambertMaterial black(0.2f);
    LambertMaterial white(0.8f);

    Texture checkers
    (
        2, 2,  // width, height 
        { &black, &white,
          &white, &black }  // pattern
    );

    PlaneGeometry plane_geometry;
    Object3D floor(plane_geometry, checkers);
    
    Scene scene; 
    scene.add(floor);

    Camera camera;
    camera.translation() = Vector3(0, 3, -5);
    camera.look_at(0, 0, 0);
    camera.update();

    Composer composer
    (
        IMAGE_WIDTH, IMAGE_HEIGHT, 
        scene, camera
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
    
    save(composer.image());
}

#include <iris/color.h>


using namespace iris;


Vector3 color::from_hex(const int value)
{
    return Vector3
    (
        ((value >> 16) & 0xFF) / 255.0f,
        ((value >> 8) & 0xFF) / 255.0f,
        ((value) & 0xFF) / 255.0f
    );
}

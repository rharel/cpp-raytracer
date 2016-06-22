#include <iris/MirrorMaterial.h>


using namespace iris;


const float EPSILON = 0.001f;

MirrorMaterial::MirrorMaterial() {}

Vector3 MirrorMaterial::brdf() const
{
    return Vector3(1);
}
Vector3 MirrorMaterial::brdf(const Vector3& Wi, const Vector3& Wo) const
{
    using glm::reflect;
    using glm::length2;

    const Vector3 reflection = reflect(-Wi, Vector3(0, 1, 0));
    if (length2(Wo - reflection) < EPSILON)
    {
        return Vector3(1); 
    }
    else 
    { 
        return Vector3(0); 
    }
}

Vector3 MirrorMaterial::bounce(const Vector3& Wi, float& pdf) const
{
    pdf = 1.0f;
    return glm::reflect(-Wi, Vector3(0, 1, 0));
}

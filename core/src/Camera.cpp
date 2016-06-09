#include <iris/Camera.h>

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>


using namespace iris;


Camera::Camera()
    : Camera(glm::radians(100.0f), 1.0f, 0.1f, 100.0f) {}
Camera::Camera(

    const float fov, const float aspect,
    const float near, const float far
)
    : fov_(fov), aspect_(aspect),
      near_(near), far_(far) {}

void Camera::update()
{
    SceneComponent::update();

    const Matrix4& W = global_transform();
    
    position_ = Vector3(W[3]);
    
    if (is_free() || position() == target())
    {
        Matrix4 R = W;
        R[3] = Vector4(0, 0, 0, 1);
        const Vector3 offset = glm::normalize(

            Vector3(R * Vector4(0, 0, -1, 1))
        );
        look_at(position() + offset);
    }

    Vector3 X, Y, Z;
    Y = Vector3(0, 1, 0);
    Z = glm::normalize(position() - target());
    if (Z == Y)
    {
        Z.x += 0.01f;
        Z = glm::normalize(Z);
    }
    X = glm::cross(-Z, Y);
    Y = glm::cross(Z, X);

    right_ = X;
    up_ = Y;
    forward_ = -Z;
}

void Camera::look_at(
    
    const float x, const float y, const float z)
{
    look_at(Vector3(x, y, z));
}
void Camera::look_at(const Vector3& target)
{
    free_ = false;
    target_ = target;
}

bool Camera::is_free() const
{
    return free_;
}
void Camera::free()
{
    free_ = true;
}

float Camera::fov() const
{
    return fov_;
}
float Camera::aspect() const
{
    return aspect_;
}
float Camera::near() const
{
    return near_;
}
float Camera::far() const
{
    return far_;
}
const Vector3& Camera::position() const
{
    return position_;
}
const Vector3& Camera::forward() const
{
    return forward_;
}
const Vector3& Camera::up() const
{
    return up_;
}
const Vector3& Camera::right() const
{
    return right_;
}
const Vector3& Camera::target() const
{
    return target_;
}

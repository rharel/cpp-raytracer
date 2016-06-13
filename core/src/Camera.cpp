#include <iris/Camera.h>

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace iris;


Camera::Camera()
    : Camera(glm::radians(100.0f), 1.0f, 0.1f, 100.0f) {}
Camera::Camera
(
    const float fov, const float aspect,
    const float near, const float far
)
    : fov_(fov), aspect_(aspect),
      near_(near), far_(far)
{
    projection_ = glm::perspective(fov, aspect, near, far);
    projection_inverse_ = glm::inverse(projection_);

    h2_ = near * glm::tan(0.5f * fov);
    h_ = 2.0f * h2_;
    w_ = aspect * h_;
    w2_ = 0.5f *  w_;
}

      
void Camera::update()
{
    Object3D::update();

    const Matrix4& W = world_matrix();

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
    if (Z == Y || Z == -Y)
    {
        Y = Vector3(0, 0, 1);
    }
    X = glm::cross(-Z, Y);
    Y = glm::cross(Z, X);

    right_ = X;
    up_ = Y;
    forward_ = -Z;

    view_[0] = Vector4(X, 0);
    view_[1] = Vector4(Y, 0);
    view_[2] = Vector4(Z, 0);
    view_[3] = W[3];
    view_inverse_ = glm::affineInverse(view_);
}

Vector3 Camera::on_near(const float x, const float y) const
{
    // In clip space
    const float xc = -1.0f + x * 2.0f;
    const float yc = -1.0f + y * 2.0f;

    return Vector3
    (
        projection_matrix_inverse() *
        (Vector4(xc, yc, -1, 1) * near())
    );
}

void Camera::look_at
(
    const float x, 
    const float y, 
    const float z
)
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
const Matrix4& Camera::view_matrix() const
{
    return view_;
}
const Matrix4& Camera::view_matrix_inverse() const
{
    return view_inverse_;
}
const Matrix4& Camera::projection_matrix() const
{
    return projection_;
}
const Matrix4& Camera::projection_matrix_inverse() const
{
    return projection_inverse_;
}

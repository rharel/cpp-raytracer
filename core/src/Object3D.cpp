#include <iris/Object3D.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <algorithm>


using namespace iris;


Object3D::Object3D()
    : geometry_(nullptr), 
      texture_(nullptr) {}
Object3D::Object3D
(
    const Geometry& geometry, 
    const Texture& texture
)
    : geometry_(&geometry), 
      texture_(&texture) {}

bool Object3D::is_empty() const
{
    return !geometry_ || !texture_;
}

void Object3D::raycast(Raycast& result) const
{
    if (is_empty())
    { 
        for (const Object3D* child : children_)
        {
            child->raycast(result);
        }
        return;
    }

    Ray global = result.ray();
    Ray local
    (
        Vector3
        (
            world_matrix_inverse() * 
            Vector4(result.ray().origin(), 1)
        ), 
        Vector3
        (
            world_rotation_matrix_inverse() * 
            Vector4(result.ray().direction(), 1)
        )
    );
    
    result.ray(local);
    const bool hit_before = result.hit();
    const float t_before = result.time();
    geometry_->raycast(result);
    const bool hit_now = result.hit();
    const float t_now = result.time();
    if ((!hit_before && hit_now) || 
        ( hit_before && t_now < t_before))
    {
        result.contact(texture_->sample
        (
            result.u(), 
            result.v()
        ));
    }
    result.ray(global);
}

bool Object3D::has_child(Object3D& target) const
{
    return children_.find(&target) != children_.end();
}
bool Object3D::has_descendant(Object3D& target) const
{
    if (has_child(target)) { return true; }
    else
    {
        return std::any_of
        (
            children_.begin(), children_.end(),
            [&target](Object3D* child) 
            { 
                return child->has_descendant(target);
            }
        );
    }
}
bool Object3D::add_child(Object3D& target)
{
    if (&target == this || 
        this->has_descendant(target) || 
        target.has_descendant(*this)) 
    { 
        return false; 
    }
    
    if (target.has_parent())
    {
        target.parent().remove_child(target);
    }
    children_.insert(&target);
    target.parent_ = this;

    return true;
}
bool Object3D::remove_child(Object3D& target)
{
    if (!has_child(target)) { return false; }

    children_.erase(&target);
    target.parent_ = nullptr;

    return true;
}

bool Object3D::has_parent() const
{
    return parent_ != nullptr;
}
Object3D& Object3D::parent()
{
    return *parent_;
}
const Object3D& Object3D::parent() const
{
    return *parent_;
}

size_t Object3D::child_count() const
{
    return children_.size();
}
Object3D& Object3D::child(const size_t index)
{
    auto it = children_.begin();
    std::advance(it, index);

    return **it;
}
const Object3D& Object3D::child(const size_t index) const
{
    auto it = children_.begin();
    std::advance(it, index);

    return **it;
}

Vector3& Object3D::translation()
{
    return translation_;
}
const Vector3& Object3D::translation() const
{
    return translation_;
}
Vector3& Object3D::scale()
{
    return scale_;
}
const Vector3& Object3D::scale() const
{
    return scale_;
}
Vector3& Object3D::rotation()
{
    return rotation_;
}
const Vector3& Object3D::rotation() const
{
    return rotation_;
}

const Matrix4& Object3D::matrix() const
{
    return local_matrix_;
}
const Matrix4& Object3D::matrix_inverse() const
{
    return local_matrix_inverse_;
}
const Matrix4& Object3D::world_matrix() const
{
    return world_matrix_;
}
const Matrix4& Object3D::world_matrix_inverse() const
{
    return world_matrix_inverse_;
}
const Vector3& Object3D::world_translation() const
{
    return world_translation_;
}
const Matrix4& Object3D::world_rotation_matrix() const
{
    return world_rotation_matrix_;
}
const Matrix4& Object3D::world_rotation_matrix_inverse() const
{
    return world_rotation_matrix_inverse_;
}

void Object3D::update()
{
    const Matrix4 S = glm::scale(Matrix4(1), scale_);
    const Matrix4 R = glm::eulerAngleXYZ
    (
        rotation_.x, 
        rotation_.y, 
        rotation_.z
    );
    const Matrix4 T = glm::translate(Matrix4(1), translation_);
    
    local_matrix_ = T * R * S;
    local_matrix_inverse_ = glm::inverse(local_matrix_);

    if (has_parent())
    {
        world_matrix_ = parent().world_matrix() * this->matrix();
        world_matrix_inverse_ = glm::inverse(world_matrix_);
    }
    else 
    { 
        world_matrix_ = local_matrix_; 
        world_matrix_inverse_ = local_matrix_inverse_;
    }

    world_translation_ = Vector3(world_matrix_[3]);
    
    world_rotation_matrix_ = world_matrix_;
    world_rotation_matrix_[3] = Vector4(0, 0, 0, 1);
    world_rotation_matrix_inverse_ = glm::inverse(world_rotation_matrix_);

    for (Object3D* child : children_)
    {
        child->update();
    }
}

bool Object3D::operator==(const Object3D& other) const
{
    return this == &other;
}
bool Object3D::operator!=(const Object3D& other) const
{
    return !(*this == other);
}

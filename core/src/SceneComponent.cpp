#include <iris/SceneComponent.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>


using namespace iris;


bool SceneComponent::has_child(SceneComponent& target) const
{
    return children_.find(&target) != children_.end();
}
bool SceneComponent::add_child(SceneComponent& target)
{
    if (has_child(target) || &target == this) { return false; }
    
    if (target.has_parent())
    {
        target.parent().remove_child(target);
    }
    children_.insert(&target);
    target.parent_ = this;

    return true;
}
bool SceneComponent::remove_child(SceneComponent& target)
{
    if (!has_child(target)) { return false; }

    children_.erase(&target);
    target.parent_ = nullptr;

    return true;
}

bool SceneComponent::has_parent() const
{
    return parent_ != nullptr;
}
SceneComponent& SceneComponent::parent()
{
    return *parent_;
}
const SceneComponent& SceneComponent::parent() const
{
    return *parent_;
}

size_t SceneComponent::child_count() const
{
    return children_.size();
}
SceneComponent& SceneComponent::child(const size_t index)
{
    auto it = children_.begin();
    std::advance(it, index);

    return **it;
}
const SceneComponent& SceneComponent::child(const size_t index) const
{
    auto it = children_.begin();
    std::advance(it, index);

    return **it;
}

void SceneComponent::translate(

    const float x, const float y, const float z)
{
    translation_ = Vector3(x, y, z);
}
void SceneComponent::scale(

    const float x, const float y, const float z)
{
    scale_ = Vector3(x, y, z);
}
void SceneComponent::rotate(

    const float x, const float y, const float z)
{
    rotation_ = Vector3(x, y, z);
}

const Matrix4& SceneComponent::local_transform() const
{
    return local_transform_;
}
const Matrix4& SceneComponent::global_transform() const
{
    return global_transform_;
}

void SceneComponent::update()
{
    const Matrix4 S = glm::scale(Matrix4(1.0f), scale_);
    const Matrix4 R = glm::eulerAngleXYZ(rotation_.x, rotation_.y, rotation_.z);
    const Matrix4 T = glm::translate(Matrix4(1.0f), translation_);
    local_transform_ = T * R * S;
    
    if (has_parent())
    {
        global_transform_ = parent().global_transform() *
                            this->local_transform();
    }
    else { global_transform_ = local_transform_; }

    for (SceneComponent* child : children_)
    {
        child->update();
    }
}

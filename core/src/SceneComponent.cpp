#include <iris/SceneComponent.h>


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

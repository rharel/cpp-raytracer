#include <iris/Scene.h>


using namespace iris;


void Scene::add(const Object3D& object)
{
    objects_.insert(&object);
}
void Scene::add_light(const Light& light)
{
    lights_.insert(&light);
}

void Scene::raycast(Raycast& result) const
{
    for (const Object3D* object : objects_)
    {
        object->raycast(result);
    }
}
bool Scene::is_visible(const Vector3& a, const Vector3& b) const
{
    const Vector3 AB = b - a;
    Raycast collision(Ray(a, AB));
    raycast(collision);
    return !collision.hit() || 
            collision.time() > glm::length(AB);
}

size_t Scene::light_count() const
{
    return lights_.size();
}
const Light& Scene::light(const size_t index) const
{
    auto it = lights_.begin();
    std::advance(it, index);
    return **it;
}

#include <iris/Scene.h>


using namespace iris;


void Scene::add(const Object3D& object)
{
    objects_.insert(&object);
}

void Scene::raycast(Raycast& result) const
{
    for (const Object3D* object : objects_)
    {
        object->raycast(result);
    }
}

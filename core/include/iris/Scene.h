#ifndef IRIS_SCENE_H
#define IRIS_SCENE_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Scene class.
 */


#include <iris/Object3D.h>
#include <iris/Light.h>
#include <iris/Raycast.h>

#include <unordered_set>


namespace iris
{
    /**
     * The scene is a container for object3d's.
     */
    class Scene
    {
        public:
        /**
         * Adds object to scene.
         */
        void add_object(const Object3D& object);
        /**
         * Adds light to scene.
         */
        void add_light(const Light& light);

        /**
         * Checks for ray-surface intersection.
         *
         * @param[in, out] result Raycast result description.
         *
         * @details
         *  Call t_max = result.time(). 
         *  Checks for ray-surface intersections in t within (0, t_max).
         *  if t_max <= 0 than looks for any intersection in t > 0.
         */
        void raycast(Raycast& result) const;
        /**
         * Checks if a ray a -> b hits an obstruction before reaching b.
         */
        bool is_visible(const Vector3& a, const Vector3& b) const;

        /**
         * Gets object count.
         */
        size_t object_count() const;
        /**
         * Gets object at index.
         */
        const Object3D& object(size_t index) const;

        /**
         * Light count.
         */
        size_t light_count() const;
        /**
         * Gets light at index.
         */
        const Light& light(size_t index) const;

        private:
        std::unordered_set<const Object3D*> objects_;
        std::unordered_set<const Light*> lights_;
    };
}



#endif  // IRIS_SCENE_H

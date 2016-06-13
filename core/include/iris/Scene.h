#ifndef IRIS_SCENE_H
#define IRIS_SCENE_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Scene class.
 */


#include <iris/Object3D.h>

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
        void add(const Object3D& object);
        
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
        
        private:
        std::unordered_set<const Object3D*> objects_;
    };
}



#endif  // IRIS_SCENE_H

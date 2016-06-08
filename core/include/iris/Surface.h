#ifndef IRIS_SURFACE_H
#define IRIS_SURFACE_H
/**
 * @file Surface.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Surface abstract class.
 */


#include <iris/Raycast.h>
#include <iris/SceneComponent.h>
#include <iris/Texture.h>


namespace iris
{
    /**
     * The surface abstract class is the general abstraction of
     * all surfaces in the scene. It handles raycasts and transformations.
     */
    class Surface : public SceneComponent
    {
        public:
        /**
         * Creates surface with identity null texture.
         */
        Surface();
        /**
         * Creates surface with given texture.
         */
        Surface(const Texture& texture);

        /**
         * Checks for ray-surface intersection.
         *
         * @param[in, out] result Raycast result description.
         *
         * @details
         *  Call t_max = result.contact_time(). 
         *  Checks for ray-surface intersections in t within (0, t_max).
         *  if t_max <= 0 than looks for any intersection in t > 0.
         */
        virtual void raycast(Raycast& result) const = 0;

        /**
         * Gets texture.
         */
        const Texture& texture() const;

        private:
        const Texture* texture_;
    };
}


#endif  // IRIS_SURFACE_H

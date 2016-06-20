#ifndef IRIS_GEOMETRY_H
#define IRIS_GEOMETRY_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Geometry abstract class.
 */


#include <iris/Raycast.h>


namespace iris
{
    /**
     * Geometries define shapes onto which rays can be cast.
     */
    class Geometry
    {
        public:
        /**
         * Checks for ray-geometry intersection.
         *
         * @param[in, out] result Raycast collision description.
         *
         * @details
         *  Call t_max = result.time(). 
         *  Checks for ray-surface intersections in t within (0, t_max).
         *  if t_max <= 0 than looks for any intersection in t > 0.
         */
        virtual void raycast(Raycast& result) const = 0;

        bool operator==(const Geometry& other) const;
        bool operator!=(const Geometry& other) const;
    };
}


#endif  // IRIS_GEOMETRY_H

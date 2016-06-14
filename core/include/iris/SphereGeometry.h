#ifndef IRIS_SPHERE_GEOMETRY_H
#define IRIS_SPHERE_GEOMETRY_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Sphere geometry class.
 */


#include <iris/Geometry.h>


namespace iris
{
    /**
     * Spherical geometry.
     */
    class SphereGeometry : public Geometry
    {
        public:
        static const Vector3 center;
        static const float radius;

        /**
         * Creates the unit sphere at the origin.
         */
        SphereGeometry();
        /**
         * Creates geometry with given texture scale.
         *
         * @param sx Texture scale along the u axis.
         * @param sy Texture scale along the v axis.
         */
        SphereGeometry(float su, float sv);

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
        void raycast(Raycast& result) const override;

        /**
         * Gets texture scale.
         */
        const Vector2& texture_scale() const;

        private:
        Vector2 texture_scale_;
    };
}


#endif  // IRIS_SPHERE_GEOMETRY_H

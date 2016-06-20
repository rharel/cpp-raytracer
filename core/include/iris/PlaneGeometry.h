#ifndef IRIS_PLANE_GEOMETRY_H
#define IRIS_PLANE_GEOMETRY_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Plane geometry class.
 */


#include <iris/Geometry.h>
#include <iris/Raycast.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * The plane geometry is an infinite plane through the origin,
     * normal N = (0, 1, 0), and texture axes u = (1, 0, 0); v = (0, 0, 1).
     */
    class PlaneGeometry : public Geometry
    {
        public:
        static const Vector3 anchor;
        static const Vector3 normal;
        static const Vector3 U, V;

        /**
         * Creates default geometry with texture scale = (1, 1).
         */
        PlaneGeometry();
        /**
         * Creates geometry with given texture scale.
         *
         * @param su Texture scale along the u axis.
         * @param sv Texture scale along the v axis.
         */
        PlaneGeometry(float su, float sv);

        /**
         * Checks for ray-geometry intersection.
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


#endif  // IRIS_PLANE_GEOMETRY_H

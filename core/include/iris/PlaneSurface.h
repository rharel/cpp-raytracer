#ifndef IRIS_PLANE_SURFACE_H
#define IRIS_PLANE_SURFACE_H
/**
 * @file PlaneSurface.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Plane surface class.
 */


#include <iris/Surface.h>


namespace iris
{
    /**
     * The plane surface is an infinite plane implicitly defined
     * through a point on the plane and its normal.
     */
    class PlaneSurface : public Surface
    {
        public:
        /**
         * Creates surface with identity null texture.
         */
        PlaneSurface();
        /**
         * Creates surface with given texture.
         */
        PlaneSurface(const Texture& texture,
                     const Vector2& texture_tile_size);

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
        void raycast(Raycast& result) const override;

        const Vector2& texture_tile_size() const;
        const Vector3& anchor() const;
        const Vector3& normal() const;
        const Vector3& U() const;
        const Vector3& V() const;

        private:
        Vector2 texture_tile_size_;

        Vector3 anchor_ = Vector3(0, 0, 0);
        Vector3 normal_ = Vector3(0, 1, 0);
        Vector3 U_ = Vector3(1, 0, 0); 
        Vector3 V_ = Vector3(0, 0, 1);
    };
}


#endif  // IRIS_PLANE_SURFACE_H

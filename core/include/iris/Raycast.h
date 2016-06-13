#ifndef IRIS_RAYCAST_H
#define IRIS_RAYCAST_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Raycast class.
 */


#include <iris/Material.h>
#include <iris/Ray.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * Raycast descriptor. Contains information about any
     * ray-geometry contacts (if any) and their properties.
     */
    class Raycast
    {
        public:
        /**
         * Creates the null raycast with null ray.
         */
        Raycast();
        /**
         * Creates raycast for given ray.
         */
        Raycast(const Ray& ray);

        /**
         * Gets ray query.
         */
        const Ray& ray() const;

        /**
         * Check whether time() > 0.
         */
        bool hit() const;
        /**
         * Computes ray.origin() + time() * ray.direction().
         */
        Vector3 point() const;

        /**
         * Gets contact time.
         */
        float time() const;
        /**
         * Gets contact normal.
         */
        const Vector3& normal() const;
        /**
         * Gets contact u texture coordinate.
         */
        float u() const;
        /**
         * Gets contact v texture coordinate.
         */
        float v() const;
        /**
         * Gets contact (u, v) texture coordinates.
         */
        const Vector2& uv() const;
        /**
         * Gets contact material.
         */
        const Material& material() const;
        /**
         * Sets contact time, normal, and (u, v) coordinates.
         */
        void contact
        (
            float time, 
            const Vector3& normal, 
            const Vector2& uv
        );
        /**
         * Sets contact material.
         */
        void contact(const Material& material);

        private:
        Ray ray_;
        float time_ = -1.0f;
        Vector3 normal_ = Vector3(0);
        Vector2 uv_ = Vector2(0);
        const Material* material_ = nullptr;
    };
}


#endif  // IRIS_RAYCAST_H

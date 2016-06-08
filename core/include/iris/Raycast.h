#ifndef IRIS_RAYCAST_H
#define IRIS_RAYCAST_H
/**
 * @file Raycast.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Raycast class.
 */


#include <iris/Material.h>
#include <iris/Ray.h>


namespace iris
{
    /**
     * Raycast descriptor. Contains information about any
     * ray-surface contacts (if any) and their properties.
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
         * Gets contact time.
         */
        float contact_time() const;
        /**
         * Gets contact normal.
         */
        const Vector3& contact_normal() const;
        /**
         * Gets contact material.
         */
        const Material& contact_material() const;
        /**
         * Sets contact info.
         */
        void contact(float time, 
                     const Vector3& normal, 
                     const Material& material);
        
        private:
        Ray ray_;
        float contact_time_ = -1.0f;
        Vector3 contact_normal_ = Vector3(0, 0, 0);
        const Material* contact_material_ = nullptr;
    };
}


#endif  // IRIS_RAYCAST_H

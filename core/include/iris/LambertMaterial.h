#ifndef IRIS_LAMBERT_MATERIAL_H
#define IRIS_LAMBERT_MATERIAL_H
/**
 * @file LambertMaterial.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Lambertian materials.
 */


#include <iris/Material.h>
#include <iris/VectorTypes.h>


namespace iris
{
    /**
     * Lambertian material.
     */
    class LambertMaterial : public Material
    {
        public:
        /**
         * Creates the null material./
         */
        LambertMaterial();
        /**
         * Creates a new material with given id and albedo.
         *
         * @note id = 0 is reserved for the null material.
         */
        LambertMaterial(int id, const Vector3& albedo);

        /**
         * Gets albedo.
         */
        const Vector3& albedo() const;
        
        private:
        Vector3 albedo_;
    };
}


#endif  // IRIS_LAMBERT_MATERIAL_H

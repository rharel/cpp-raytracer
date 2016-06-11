#ifndef IRIS_LAMBERT_MATERIAL_H
#define IRIS_LAMBERT_MATERIAL_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Lambertian material.
 */


#include <iris/Material.h>
#include <iris/vector_types.h>


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
         * @note id = -1 is reserved for the null material.
         */
        LambertMaterial(int id, const Vector3& albedo);

        /**
         * Evaluates the BRDF's integral.
         */
        Vector3 brdf() const override;
        /**
         * Evaluates the BRDF for given incoming/outgoing 
         * ray directions.
         *
         * @param Wi Incoming ray direction.
         * @param Wo Outgoing ray direction.
         *
         * @note Assumes normal at contact point is N = (0, 1, 0).
         */
        Vector3 brdf
        (
            const Vector3& Wi, 
            const Vector3& Wo
        ) const override;

        /**
         * Gets albedo.
         */
        const Vector3& albedo() const;
        
        private:
        Vector3 albedo_;
    };
}


#endif  // IRIS_LAMBERT_MATERIAL_H

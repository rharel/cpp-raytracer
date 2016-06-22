#ifndef IRIS_MIRROR_MATERIAL_H
#define IRIS_MIRROR_MATERIAL_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Mirror material.
 */


#include <iris/Material.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * Lambertian material.
     */
    class MirrorMaterial : public Material
    {
        public:
        /**
         * Creates material./
         */
        MirrorMaterial();
        
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
         * Bounces a ray to a new random direction.
         *
         * @param      Wi  Incoming ray direction.
         * @param[out] pdf Probability of chosen outgoing direction.
         *
         * @returns Outgoing direction.
         *
         * @note Assumes normal at contact point is N = (0, 1, 0).
         */
        Vector3 bounce(const Vector3& Wi, float& pdf) const;
    };
}


#endif  // IRIS_MIRROR_MATERIAL_H

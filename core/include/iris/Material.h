#ifndef IRIS_MATERIAL_H
#define IRIS_MATERIAL_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Material abstract class.
 */


#include <iris/vector_types.h>


namespace iris
{
    /**
     * The material interface embodies a bi-directional 
     * distribution function (BRDF).
     */
    class Material
    {
        public:
        /**
         * Evaluates the BRDF's integral.
         */
        virtual Vector3 brdf() const = 0;
        /**
         * Evaluates the BRDF for given incoming/outgoing 
         * ray directions.
         *
         * @param Wi Incoming ray direction.
         * @param Wo Outgoing ray direction.
         *
         * @note Assumes normal at contact point is N = (0, 1, 0).
         */
        virtual Vector3 brdf
        (
            const Vector3& Wi, 
            const Vector3& Wo
        ) const = 0;

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
        virtual Vector3 bounce(const Vector3& Wi, float& pdf) const = 0;

        bool operator==(const Material& other) const;
        bool operator!=(const Material& other) const;
    };
}


#endif  // IRIS_MATERIAL_H

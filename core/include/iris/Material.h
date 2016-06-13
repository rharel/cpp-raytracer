#ifndef IRIS_MATERIAL_H
#define IRIS_MATERIAL_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Material interface.
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
        virtual Vector3 brdf() const;
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
        ) const;

        bool operator==(const Material& other) const;
        bool operator!=(const Material& other) const;
    };
}


#endif  // IRIS_MATERIAL_H

#ifndef IRIS_RANDOM_H
#define IRIS_RANDOM_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Random utility methods.
 */


#include <random>
#include <type_traits>


namespace iris
{
    namespace random
    {
        #ifdef _DEBUG
        static std::mt19937 engine_;  // use default seed
        #else
        static std::random_device device_;
        static std::mt19937 engine_(device_());
        #endif

        /**
         * Gets random integral type in range.
         */
        template<typename IntegralType>
        IntegralType int_in_range(IntegralType min, IntegralType max)
        {
            static_assert(std::is_integral<IntegralType>::value, 
                          "integral type required");
            
            std::uniform_int_distribution<IntegralType> distribution(min, max);
            return distribution(engine_);
        }
        /**
         * Gets random real type in range.
         */
        template<typename RealType>
        RealType real_in_range(RealType min, RealType max)
        {
            static_assert(std::is_arithmetic<RealType>::value, 
                          "real type required");
            
            std::uniform_real_distribution<RealType> distribution(min, max);
            return distribution(engine_);
        }
    }
}


#endif  // IRIS_RANDOM_H

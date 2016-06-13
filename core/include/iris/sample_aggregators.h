#ifndef IRIS_SAMPLE_AGGREGATORS_H
#define IRIS_SAMPLE_AGGREGATORS_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Sample weighing methods.
 */


#include <iris/vector_types.h>


namespace iris
{
    namespace aggregate
    {
        template
        <
            typename Vector3Iterable,
            typename Vector2Iterable
        >
        Vector3 uniform
        (
            Vector3Iterable colors, 
            Vector2Iterable samples
        );
    }
}


#include <iris/sample_aggregators.hpp>


#endif  // IRIS_SAMPLE_AGGREGATORS_H

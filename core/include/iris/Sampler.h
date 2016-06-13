#ifndef IRIS_SAMPLER_H
#define IRIS_SAMPLER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Sampler abstract class.
 */


#include <iris/vector_types.h>


namespace iris
{
    /**
     * Samples sub-pixel positions.
     *
     * @details
     *      The sampler is a generator for sub-pixel positions.
     *      While has_next() is true, the sampler has more positions
     *      to output. After each position is yielded through next(),
     *      It is expected that the color of the ray traced through 
     *      that position will be reported back via report() - this 
     *      is required for adaptive sampling techniques.
     *      So, usage looks roughly as follows:
     *          Sampler s;
     *          for (pixel in image) 
     *          {
     *              s.reset();
     *              while (s.has_next())
     *              {
     *                  position = s.next();
     *                  s.report(trace(pixel + position))
     *              }
     *          }
     */
    class Sampler
    {
        public:
        /**
         * Resets sampler state.
         */
        virtual void reset() = 0;
        /**
         * Checks if there are more samples to be output.
         */
        virtual bool has_next() const = 0;
        /**
         * Yields the next sample in pixel-normalized coordinates.
         */
        virtual Vector2 next() = 0;
        /**
         * Processses the traced ray color for the last output sample.
         */
        virtual void report(const Vector3& color) = 0;
    };
}


#endif  // IRIS_SAMPLER_H

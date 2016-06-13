#ifndef IRIS_RAY_H
#define IRIS_RAY_H
/**
 * @file Ray.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Ray class.
 */


#include <iris/vector_types.h>


namespace iris
{
    /**
     * Ray descriptor with origin and direction.
     */
    class Ray
    {
        public:
        /**
         * Creates the null ray with direction (0, 0, 0).
         */
        Ray();
        /**
         * Creates a ray with given direction and origin at (0, 0, 0).
         */
        Ray(const Vector3& direction);
        /**
         * Creates a ray from given origin and direction.
         */
        Ray(const Vector3& origin, const Vector3& direction);
        
        /**
         * Checks if direction is (0, 0, 0).
         */
        bool is_null() const;

        /**
         * Evaluate ray at given time.
         */
        Vector3 at(float time) const;

        /**
         * Gets ray origin.
         */
        const Vector3& origin() const;
        /**
         * Gets ray direction.
         */
        const Vector3& direction() const;

        bool operator==(const Ray& other) const;
        bool operator!=(const Ray& other) const;

        private:
        Vector3 origin_;
        Vector3 direction_;
    };
}


#endif  // IRIS_RAY_H

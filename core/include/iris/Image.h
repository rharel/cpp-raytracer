#ifndef IRIS_IMAGE_H
#define IRIS_IMAGE_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Image class.
 */


#include <iris/vector_types.h>

#include <vector>


namespace iris
{
    /**
     * Image descriptor.
     */
    class Image
    {
        public:
        /**
         * Creates empty image.
         */
        Image();
        /**
         * Creates image with given dimensions.
         *
         * @note If width or height are zero, the image degenerates
         *       into a 0x0 one.
         */
        Image(size_t width, size_t height);

        /**
         * Gets pixel color.
         */
        const Vector3& pixel(size_t x, size_t y) const;
        /**
         * Sets pixel color.
         */
        void color_pixel(size_t x, size_t y, const Vector3& color);

        /**
         * Checks if width or height are zero.
         */
        bool is_empty() const;

        /**
         * Gets width.
         */
        size_t width() const;
        /**
         * Gets height.
         */
        size_t height() const;
        /**
         * Gets width * height.
         */
        size_t size() const;

        private:
        std::vector<std::vector<Vector3>> data_;
    };
}


#endif  // IRIS_IMAGE_H

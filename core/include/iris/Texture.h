#ifndef IRIS_TEXTURE_H
#define IRIS_TEXTURE_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Texture class.
 */


#include <iris/Material.h>
#include <iris/vector_types.h>

#include <vector>


namespace iris
{
    /**
     * The texture class defines a material spatial pattern.
     */
    class Texture
    {
        public:
        static const Texture null;

        /**
         * Creates the null texture./
         */
        Texture();
        /**
         * Creates a new texture with given id.
         *
         * @param width   Horizontal resolution.
         * @param height  Vertical resolution.
         * @param pattern Array of width * height material pointers.
         *
         * @note id = -1 is reserved for the null texture.
         */
        Texture
        (
            int id,
            size_t x, size_t y,
            std::initializer_list<const Material*> pattern
        );

        /**
         * Samples texture at given coordinates.
         */
        const Material& sample(float u, float v) const;

        /**
         * Gets id.
         */
        int id() const;
        /**
         * Gets resolution.
         */
        const Vector2u& resolution() const;

        bool operator==(const Texture& other) const;
        bool operator!=(const Texture& other) const;

        private:
        int id_;
        Vector2u resolution_;
        std::vector<const Material*> pattern_;
    };
}


#endif  // IRIS_TEXTURE_H

#ifndef IRIS_TEXTURE_H
#define IRIS_TEXTURE_H
/**
 * @file Texture.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Texture class.
 */


#include <iris/Material.h>
#include <iris/VectorTypes.h>

#include <vector>


namespace iris
{
    /**
     * The texture class defines a material spatial pattern
     * for surfaces.
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
         * @note id = 0 is reserved for the null texture.
         */
        Texture(int id,
                size_t x, size_t y,
                std::initializer_list<const Material*> data);

        /**
         * Samples texture at given coordinate.
         */
        const Material& sample(float u, float v) const;

        /**
         * Gets id.
         */
        int id() const;
        const Vector2u& resolution() const;

        bool operator==(const Texture& other) const;
        bool operator!=(const Texture& other) const;

        private:
        int id_;
        Vector2u resolution_;
        std::vector<const Material*> data_;
    };
}


#endif  // IRIS_TEXTURE_H

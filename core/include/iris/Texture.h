#ifndef IRIS_TEXTURE_H
#define IRIS_TEXTURE_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Texture class.
 */


#include <iris/Material.h>
#include <iris/LambertMaterial.h>
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
        static const LambertMaterial default_material;

        /**
         * Creates default white texture./
         */
        Texture();
        /**
         * Creates a uniform texture.
         */
        Texture(const Material& material);
        /**
         * Creates a new texture.
         *
         * @param width   Horizontal resolution.
         * @param height  Vertical resolution.
         * @param pattern Array of width * height material pointers.
         */
        Texture
        (
            size_t width, size_t height,
            std::initializer_list<const Material*> pattern
        );
        /**
         * Creates a new texture.
         *
         * @param width   Horizontal resolution.
         * @param height  Vertical resolution.
         * @param pattern Array of width * height material pointers.
         */
        Texture
        (
            size_t width, size_t height,
            const Material** pattern
        );

        /**
         * Samples texture at given coordinates.
         */
        const Material& sample(float u, float v) const;

        /**
         * Gets resolution.
         */
        const Vector2u& resolution() const;

        bool operator==(const Texture& other) const;
        bool operator!=(const Texture& other) const;

        private:
        Vector2u resolution_;
        std::vector<const Material*> pattern_;
    };
}


#endif  // IRIS_TEXTURE_H

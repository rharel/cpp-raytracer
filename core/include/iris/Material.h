#ifndef IRIS_MATERIAL_H
#define IRIS_MATERIAL_H
/**
 * @file Material.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Material interface.
 */


namespace iris
{
    /**
     * The material interface is the general abstraction of
     * all materials in the scene.
     */
    class Material
    {
        public:
        static Material null;

        /**
         * Creates the null material./
         */
        Material();
        /**
         * Creates a new material with given id.
         *
         * @note id = 0 is reserved for the null material.
         */
        Material(int id);

        /**
         * Gets id.
         */
        int id() const;

        bool operator==(const Material& other) const;
        bool operator!=(const Material& other) const;

        private:
        int id_;
    };
}



#endif  // IRIS_MATERIAL_H

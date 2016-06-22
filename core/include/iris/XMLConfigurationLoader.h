#ifndef IRIS_XML_CONFIGURATION_LOADER_H
#define IRIS_XML_CONFIGURATION_LOADER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * XMLConfigurationLoader class.
 */


#include <iris/ConfigurationLoader.h>

#include <iris/Material.h>
#include <iris/Texture.h>
#include <iris/Geometry.h>
#include <iris/Object3D.h>
#include <iris/Light.h>
#include <iris/vector_types.h>

#include "../lib/tinyxml2/tinyxml2.h"

#include <string>
#include <vector>


namespace iris
{
    /**
     * Reads external scenes and tracing configurations from xml files.
     */
    class XMLConfigurationLoader : public ConfigurationLoader
    {
        public:
        static const char* ELEMENT_CONFIGURATION;
        static const char* ELEMENT_MATERIALS;
        static const char* ELEMENT_MATERIAL;
        static const char* ELEMENT_TEXTURES;
        static const char* ELEMENT_TEXTURE;
        static const char* ELEMENT_GEOMETRIES;
        static const char* ELEMENT_GEOMETRY;
        static const char* ELEMENT_SCENE;
        static const char* ELEMENT_OBJECTS;
        static const char* ELEMENT_OBJECT;
        static const char* ELEMENT_LIGHTS;
        static const char* ELEMENT_LIGHT;
        static const char* ELEMENT_SAMPLER;
        static const char* ELEMENT_TRACER;
        static const char* ELEMENT_CAMERA;
        static const char* ELEMENT_IMAGE;

        static const char* ATTRIBUTE_NAME;
        static const char* ATTRIBUTE_TYPE;
        static const char* ATTRIBUTE_WIDTH;
        static const char* ATTRIBUTE_HEIGHT;
        static const char* ATTRIBUTE_ALBEDO;
        static const char* ATTRIBUTE_PATTERN;
        static const char* ATTRIBUTE_TEXTURE_SCALE_U;
        static const char* ATTRIBUTE_TEXTURE_SCALE_V;
        static const char* ATTRIBUTE_GEOMETRY;
        static const char* ATTRIBUTE_TEXTURE;
        static const char* ATTRIBUTE_TRANSLATION;
        static const char* ATTRIBUTE_SCALE;
        static const char* ATTRIBUTE_ROTATION;
        static const char* ATTRIBUTE_COLOR;
        static const char* ATTRIBUTE_INTENSITY;
        static const char* ATTRIBUTE_DEGREE;
        static const char* ATTRIBUTE_FOV;
        static const char* ATTRIBUTE_ASPECT;
        static const char* ATTRIBUTE_NEAR;
        static const char* ATTRIBUTE_FAR;
        static const char* ATTRIBUTE_LOOK_AT;
        static const char* ATTRIBUTE_PATH;
        static const char* ATTRIBUTE_PRECISION;

        static const char* VALUE_LAMBERT;
        static const char* VALUE_PLANE;
        static const char* VALUE_SPHERE;
        static const char* VALUE_NAIVE;
        static const char* VALUE_RANDOM;
        static const char* VALUE_JITTER;
        static const char* VALUE_PATH;

        static const char HEX_SYMBOL;

        static const char DELIMETER;
        
        /**
         * Reads scene from path.
         *
         * @details
         *   The return value of status() post-call will be:
         *     Success - when operation completes succesfully.
         *     FileError - when path cannot be accessed.
         *     ParsingError - when path contents could not be parsed.
         *     InternalError - when an unexpected internal failure occurs.
         */
        Configuration load_from_path(const std::string& path) override;
        /**
         * Reads scene from path.
         *
         * @details
         *   The return value of status() post-call will be:
         *     Success - when operation completes succesfully.
         *     ParsingError - when string contents could not be parsed.
         *     InternalError - when an unexpected internal failure occurs.
         */
        Configuration load_from_string(const std::string& xml) override;

        private:
        typedef tinyxml2::XMLElement Element;

        bool require_has_child
        (
            const Element* target,
            const char* name
        );
        bool require_has_attributes
        (
            const Element* target,
            const std::vector<const char*>& attribute_names
        );

        void parse_configuration(const Element* source);

        void parse_materials(const Element* source);
        Material* parse_material_lambert(const Element* source);

        void parse_textures(const Element* source);
        Texture* parse_texture(const Element* source);

        void parse_geometries(const Element* source);
        Geometry* parse_geometry_plane(const Element* source);
        Geometry* parse_geometry_sphere(const Element* source);
        
        void parse_scene(const Element* source);
        
        void parse_objects(const Element* source, Object3D* parent);
        Object3D* parse_object(const Element* source, Object3D* parent);
        
        void parse_lights(const Element* source);
        Light* parse_light_sphere(const Element* source);

        void parse_sampler(const Element* source);
        void parse_tracer(const Element* source);
        void parse_camera(const Element* source);
        void parse_image(const Element* source);

        Vector3 parse_color(const char* string);
        Vector3 parse_vector3(const char* string);

        Configuration configuration_;
    };
}


#endif  // IRIS_XML_CONFIGURATION_LOADER_H

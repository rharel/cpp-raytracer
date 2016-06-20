#ifndef IRIS_SCENE_READER_H
#define IRIS_SCENE_READER_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * SceneReader abstract class.
 */


#include <iris/Material.h>
#include <iris/Texture.h>
#include <iris/Geometry.h>
#include <iris/Scene.h>
#include <iris/Object3D.h>
#include <iris/Light.h>
#include <iris/Sampler.h>
#include <iris/Raytracer.h>
#include <iris/Camera.h>

#include <memory>
#include <string>
#include <unordered_map>


namespace iris
{
    /**
     * Scene and tracing-configuration descriptor.
     */
    class Configuration
    {
        public:
        typedef std::string ID;
        typedef std::shared_ptr<Material> MaterialPtr;
        typedef std::shared_ptr<Texture> TexturePtr;
        typedef std::shared_ptr<Geometry> GeometryPtr;
        typedef std::shared_ptr<Scene> ScenePtr;
        typedef std::shared_ptr<Object3D> ObjectPtr;
        typedef std::shared_ptr<Light> LightPtr;
        typedef std::shared_ptr<Sampler> SamplerPtr;
        typedef std::shared_ptr<Raytracer> TracerPtr;
        typedef std::unordered_map<ID, MaterialPtr> MaterialMap;
        typedef std::unordered_map<ID, TexturePtr> TextureMap;
        typedef std::unordered_map<ID, GeometryPtr> GeometryMap;
        typedef std::vector<ObjectPtr> ObjectList;
        typedef std::vector<LightPtr> LightList;

        MaterialMap materials;
        TextureMap textures;
        GeometryMap geometries;
        ObjectList objects;
        LightList lights;
        ScenePtr scene;
        SamplerPtr sampler;
        TracerPtr tracer;
        Camera camera;
        Vector2u image_size = Vector2u(256, 256);
        std::string image_path = ".";
    };
    /**
     * Reads external scenes and tracing configurations.
     */
    class SceneReader
    {
        public:
        enum class Status : int
        {
            Success,
            FileError,
            ParsingError,
            InternalError
        };

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
        virtual Configuration read_from_path(const std::string& path) = 0;
        /**
         * Reads scene from path. 
         *
         * @details
         *   The return value of status() post-call will be:
         *     Success - when operation completes succesfully.
         *     ParsingError - when string contents could not be parsed.
         *     InternalError - when an unexpected internal failure occurs.
         */
        virtual Configuration read_from_string(const std::string& xml) = 0;

        /**
         * Gets status. Query this after calls to various read methods.
         */
        Status status() const;
        /**
         * Gets status message if available.
         */
        const std::string& status_message() const;

        protected:
        Status status_ = Status::Success;
        std::string status_message_;
    };
}


#endif  // IRIS_SCENE_READER_H

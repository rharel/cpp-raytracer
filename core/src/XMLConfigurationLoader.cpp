#include <iris/XMLConfigurationLoader.h>

#include <iris/LambertMaterial.h>

#include <iris/PlaneGeometry.h>
#include <iris/SphereGeometry.h>

#include <iris/Scene.h>

#include <iris/SphereLight.h>

#include <iris/NaiveSampler.h>
#include <iris/RandomSampler.h>
#include <iris/JitterSampler.h>

#include <iris/NaiveTracer.h>
#include <iris/PathTracer.h>

#include <iris/color.h>
#include <iris/string.h>

#include <fstream>
#include <sstream>
#include <queue>


using namespace iris;
using namespace tinyxml2;
using MaterialPtr = Configuration::MaterialPtr;
using MaterialMap = Configuration::MaterialMap;
using TexturePtr = Configuration::TexturePtr;
using TextureMap = Configuration::TextureMap;
using GeometryPtr = Configuration::GeometryPtr;
using GeometryMap = Configuration::GeometryMap;
using ScenePtr = Configuration::ScenePtr;
using ObjectPtr = Configuration::ObjectPtr;
using ObjectList = Configuration::ObjectList;
using LightPtr = Configuration::LightPtr;
using LightList = Configuration::LightList;
using SamplerPtr = Configuration::SamplerPtr;
using TracerPtr = Configuration::TracerPtr;
using std::string;


const char* XMLConfigurationLoader::ELEMENT_CONFIGURATION = "configuration";
const char* XMLConfigurationLoader::ELEMENT_MATERIALS = "materials";
const char* XMLConfigurationLoader::ELEMENT_MATERIAL = "material";
const char* XMLConfigurationLoader::ELEMENT_TEXTURES = "textures";
const char* XMLConfigurationLoader::ELEMENT_TEXTURE = "texture";
const char* XMLConfigurationLoader::ELEMENT_GEOMETRIES = "geometries";
const char* XMLConfigurationLoader::ELEMENT_GEOMETRY = "geometry";
const char* XMLConfigurationLoader::ELEMENT_SCENE = "scene";
const char* XMLConfigurationLoader::ELEMENT_OBJECTS = "objects";
const char* XMLConfigurationLoader::ELEMENT_OBJECT = "object";
const char* XMLConfigurationLoader::ELEMENT_LIGHTS = "lights";
const char* XMLConfigurationLoader::ELEMENT_LIGHT = "light";
const char* XMLConfigurationLoader::ELEMENT_SAMPLER = "sampler";
const char* XMLConfigurationLoader::ELEMENT_TRACER = "tracer";
const char* XMLConfigurationLoader::ELEMENT_CAMERA = "camera";
const char* XMLConfigurationLoader::ELEMENT_IMAGE = "image";

const char* XMLConfigurationLoader::ATTRIBUTE_NAME = "name";
const char* XMLConfigurationLoader::ATTRIBUTE_TYPE = "type";
const char* XMLConfigurationLoader::ATTRIBUTE_WIDTH = "width";
const char* XMLConfigurationLoader::ATTRIBUTE_HEIGHT = "height";
const char* XMLConfigurationLoader::ATTRIBUTE_ALBEDO = "albedo";
const char* XMLConfigurationLoader::ATTRIBUTE_PATTERN = "pattern";
const char* XMLConfigurationLoader::ATTRIBUTE_TEXTURE_SCALE_U = "textureScaleU";
const char* XMLConfigurationLoader::ATTRIBUTE_TEXTURE_SCALE_V = "textureScaleV";
const char* XMLConfigurationLoader::ATTRIBUTE_GEOMETRY = "geometry";
const char* XMLConfigurationLoader::ATTRIBUTE_TEXTURE = "texture";
const char* XMLConfigurationLoader::ATTRIBUTE_TRANSLATION = "translation";
const char* XMLConfigurationLoader::ATTRIBUTE_SCALE = "scale";
const char* XMLConfigurationLoader::ATTRIBUTE_ROTATION = "rotation";
const char* XMLConfigurationLoader::ATTRIBUTE_COLOR = "color";
const char* XMLConfigurationLoader::ATTRIBUTE_INTENSITY = "intensity";
const char* XMLConfigurationLoader::ATTRIBUTE_DEGREE = "degree";
const char* XMLConfigurationLoader::ATTRIBUTE_FOV = "fov";
const char* XMLConfigurationLoader::ATTRIBUTE_ASPECT = "aspect";
const char* XMLConfigurationLoader::ATTRIBUTE_NEAR = "near";
const char* XMLConfigurationLoader::ATTRIBUTE_FAR = "far";
const char* XMLConfigurationLoader::ATTRIBUTE_LOOK_AT = "lookAt";
const char* XMLConfigurationLoader::ATTRIBUTE_PATH = "path";

const char* XMLConfigurationLoader::VALUE_LAMBERT = "lambert";
const char* XMLConfigurationLoader::VALUE_PLANE = "plane";
const char* XMLConfigurationLoader::VALUE_SPHERE = "sphere";
const char* XMLConfigurationLoader::VALUE_NAIVE = "naive";
const char* XMLConfigurationLoader::VALUE_RANDOM = "random";
const char* XMLConfigurationLoader::VALUE_JITTER = "jitter";
const char* XMLConfigurationLoader::VALUE_PATH = "path";

const char XMLConfigurationLoader::HEX_SYMBOL = '#';

const char XMLConfigurationLoader::DELIMETER = ',';

Configuration XMLConfigurationLoader::load_from_path(const string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        status_ = Status::FileError;
        return Configuration();
    }
    std::stringstream contents;
    contents << file.rdbuf();
    return load_from_string(contents.str());
}
Configuration XMLConfigurationLoader::load_from_string(const string& xml)
{
    configuration_ = Configuration();
    
    status_ = Status::Success;
    status_message_ = "";

    XMLDocument doc;
    if (doc.Parse(xml.c_str()) != XML_NO_ERROR)
    {
        status_ = Status::ParsingError;
        status_message_ = "Could not parse XML";
        return configuration_;
    }
    Element* e_configuration = doc.FirstChildElement(ELEMENT_CONFIGURATION);
    if (e_configuration == nullptr) { return configuration_; }
    parse_configuration(e_configuration);
    return configuration_;
}

bool XMLConfigurationLoader::require_has_child
(
    const Element* target,
    const char* name
)
{
    if (target->FirstChildElement(name) == nullptr)
    {
        status_ = Status::ParsingError;
        status_message_ = "Missing child of "
                          "<" + string(target->Name()) + ">: " +
                          "<" + string(name) + ">";
        return false;
    }
    else { return true; }
}
bool XMLConfigurationLoader::require_has_attributes
(
    const Element* target,
    const std::vector<const char*>& attribute_names
)
{
    for (const char* name : attribute_names)
    {
        if (target->Attribute(name) == nullptr)
        {
            status_ = Status::ParsingError;
            status_message_ = "Missing attribute for "
                              "<" + string(target->Name()) + ">: " +
                              "'" + string(name) + "'";
            return false;
        }
    }
    return true;
}

void XMLConfigurationLoader::parse_configuration(const Element* source)
{
    const Element* e_materials = source->FirstChildElement(ELEMENT_MATERIALS);
    const Element* e_textures = source->FirstChildElement(ELEMENT_TEXTURES);
    const Element* e_geometries = source->FirstChildElement(ELEMENT_GEOMETRIES);
    const Element* e_scene = source->FirstChildElement(ELEMENT_SCENE);
    const Element* e_sampler = source->FirstChildElement(ELEMENT_SAMPLER);
    const Element* e_tracer = source->FirstChildElement(ELEMENT_TRACER);
    const Element* e_camera = source->FirstChildElement(ELEMENT_CAMERA);
    const Element* e_image = source->FirstChildElement(ELEMENT_IMAGE);

    if (e_materials != nullptr)
    {
        parse_materials(e_materials);
        if (status() != Status::Success) { return; }
        if (e_textures != nullptr)
        {
            parse_textures(e_textures);
            if (status() != Status::Success) { return; }
        }
    }
    if (e_geometries != nullptr)
    {
        parse_geometries(e_geometries);
        if (status() != Status::Success) { return; }
    }
    if (e_materials != nullptr &&
        e_textures != nullptr &&
        e_geometries != nullptr &&
        e_scene != nullptr)
    {
        parse_scene(e_scene);
        if (status() != Status::Success) { return; }
    }
    parse_sampler(e_sampler);
    parse_tracer(e_tracer);
    parse_camera(e_camera);
    parse_image(e_image);
}

void XMLConfigurationLoader::parse_materials(const Element* source)
{
    if (!require_has_child(source, ELEMENT_MATERIAL)) { return; }
    const std::vector<const char*> required_attributes
    { 
        ATTRIBUTE_NAME, ATTRIBUTE_TYPE 
    };
    const Element* child = source->FirstChildElement(ELEMENT_MATERIAL);
    while (child != nullptr)
    {
        if (!require_has_attributes(child, required_attributes)) { return; }
        const char* name = child->Attribute(ATTRIBUTE_NAME);
        const char* type = child->Attribute(ATTRIBUTE_TYPE);
        if (strcmp(type, VALUE_LAMBERT) == 0)
        {
            configuration_.materials[name] = MaterialPtr
            (
                parse_material_lambert(child)
            );
        }
        else
        {
            status_ = Status::ParsingError;
            status_message_ = "Unknown material type: " + string(type);
        }
        if (status() != Status::Success) { return; }
        child = child->NextSiblingElement(ELEMENT_MATERIAL);
    }
}
Material* XMLConfigurationLoader::parse_material_lambert(const Element* source)
{
    if (!require_has_attributes(source, {ATTRIBUTE_ALBEDO})) { return nullptr; }

    const char* albedo_str = source->Attribute(ATTRIBUTE_ALBEDO);
    const Vector3 albedo = parse_color(albedo_str);
    return new LambertMaterial(albedo);
}

void XMLConfigurationLoader::parse_textures(const Element* source)
{
    if (!require_has_child(source, ELEMENT_TEXTURE)) { return; }
    const std::vector<const char*> required_attributes
    { 
        ATTRIBUTE_NAME, 
        ATTRIBUTE_WIDTH, ATTRIBUTE_HEIGHT,
        ATTRIBUTE_PATTERN
    };
    const Element* child = source->FirstChildElement(ELEMENT_TEXTURE);
    while (child != nullptr)
    {
        if (!require_has_attributes(child, required_attributes)) { return; }
        
        const char* name = child->Attribute(ATTRIBUTE_NAME);
        configuration_.textures[name] = TexturePtr(parse_texture(child));
        if (status() != Status::Success) { return; }
        
        child = child->NextSiblingElement(ELEMENT_TEXTURE);
    }
}
Texture* XMLConfigurationLoader::parse_texture(const Element* source)
{
    const size_t width = source->IntAttribute(ATTRIBUTE_WIDTH);
    const size_t height = source->IntAttribute(ATTRIBUTE_HEIGHT);
    const char* pattern_str = source->Attribute(ATTRIBUTE_PATTERN);
    if (width <= 0 || height <= 0)
    {
        status_ = Status::ParsingError;
        status_message_ = "Texture width/height is <= 0";
        return nullptr;
    }

    std::vector<const Material*> pattern;
    pattern.reserve(width * height);
    std::vector<string> material_names = split(pattern_str, DELIMETER);

    if (material_names.size() != pattern.capacity())
    {
        status_ = Status::ParsingError;
        status_message_ = "Texture-dimensions pattern-size mismatch";
        return nullptr;
    }
    for (const string& material_name : material_names)
    {
        if (configuration_.materials.find(material_name) == 
            configuration_.materials.end())
        {
            status_ = Status::ParsingError;
            status_message_ = "Unknown material name: " + material_name;
            return nullptr;
        }
        pattern.push_back(configuration_.materials.at(material_name).get());
    }
    return new Texture(width, height, &pattern[0]);
}

void XMLConfigurationLoader::parse_geometries(const Element* source)
{
    if (!require_has_child(source, ELEMENT_GEOMETRY)) { return; }
    const std::vector<const char*> required_attributes
    { 
        ATTRIBUTE_NAME, ATTRIBUTE_TYPE
    };
    const Element* child = source->FirstChildElement(ELEMENT_GEOMETRY);
    while (child != nullptr)
    {
        const char* name = child->Attribute(ATTRIBUTE_NAME);
        const char* type = child->Attribute(ATTRIBUTE_TYPE);
        if (strcmp(type, VALUE_PLANE) == 0)
        {
            configuration_.geometries[name] = GeometryPtr(parse_geometry_plane(child));
        }
        else if (strcmp(type, VALUE_SPHERE) == 0)
        {
            configuration_.geometries[name] = GeometryPtr(parse_geometry_sphere(child));
        }
        else
        {
            status_ = Status::ParsingError;
            status_message_ = "Unknown geometry type: " + 
                               string(type);
        }
        if (status() != Status::Success) { return; }
        child = child->NextSiblingElement(ELEMENT_GEOMETRY);
    }
}
Geometry* XMLConfigurationLoader::parse_geometry_plane(const Element* source)
{
    const float texture_scale_x = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_U);
    const float texture_scale_y = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_V);
    if (texture_scale_x <= 0 || texture_scale_y <= 0)
    {
        status_ = Status::ParsingError;
        status_message_ = "Texture scale is <= 0";
        return nullptr;
    }
    return new PlaneGeometry(texture_scale_x, texture_scale_y);
}
Geometry* XMLConfigurationLoader::parse_geometry_sphere(const Element* source)
{
    const float texture_scale_x = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_U);
    const float texture_scale_y = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_V);
    if (texture_scale_x <= 0 || texture_scale_y <= 0)
    {
        status_ = Status::ParsingError;
        status_message_ = "Texture scale is <= 0";
        return nullptr;
    }
    return new SphereGeometry(texture_scale_x, texture_scale_y);
}

void XMLConfigurationLoader::parse_scene(const Element* source)
{
    configuration_.scene = ScenePtr(new Scene());
    
    const Element* e_objects = source->FirstChildElement(ELEMENT_OBJECTS);
    const Element* e_lights = source->FirstChildElement(ELEMENT_LIGHTS);

    if (e_objects != nullptr)
    {
        parse_objects(e_objects, nullptr);
        if (status() != Status::Success) { return; }
    }
    if (e_lights != nullptr)
    {
        parse_lights(e_lights);
        if (status() != Status::Success) { return; }
    }
}

void XMLConfigurationLoader::parse_objects(const Element* source, Object3D* parent)
{
    if (!require_has_child(source, ELEMENT_OBJECT)) { return; }
    const Element* child = source->FirstChildElement(ELEMENT_OBJECT);
    while (child != nullptr)
    {
        Object3D* object = parse_object(child, parent);
        if (status() != Status::Success) { return; }
        
        configuration_.objects.push_back(ObjectPtr(object));
        child = child->NextSiblingElement(ELEMENT_OBJECT);
    }
}
Object3D* XMLConfigurationLoader::parse_object(const Element* source, Object3D* parent)
{
    const char* translation_str = source->Attribute(ATTRIBUTE_TRANSLATION);
    const char* scale_str = source->Attribute(ATTRIBUTE_SCALE);
    const char* rotation_str = source->Attribute(ATTRIBUTE_ROTATION);

    const char* texture_str = source->Attribute(ATTRIBUTE_TEXTURE);
    const char* geometry_str = source->Attribute(ATTRIBUTE_GEOMETRY);

    Object3D* object = nullptr;
    if (texture_str != nullptr && geometry_str != nullptr)
    {
        if (configuration_.textures.find(texture_str) == 
            configuration_.textures.end())
        {
            status_ = Status::ParsingError;
            status_message_ = "Unknown texture name: " + 
                               string(texture_str);
            return nullptr;
        }
        if (configuration_.geometries.find(geometry_str) == 
            configuration_.geometries.end())
        {
            status_ = Status::ParsingError;
            status_message_ = "Unknown geometry name: " + 
                               string(geometry_str);
            return nullptr;
        }
        object = new Object3D
        (
            *configuration_.geometries[geometry_str], 
            *configuration_.textures[texture_str]
        );
    }
    else
    {
        object = new Object3D();
        parse_objects(source, object);
        if (status() != Status::Success) { return nullptr; }
    }
    if (translation_str != nullptr)
    {
        object->translation() = parse_vector3(translation_str);
        if (status() != Status::Success) { return nullptr; }
    }
    if (scale_str != nullptr)
    {
        object->scale() = parse_vector3(scale_str);
        if (status() != Status::Success) { return nullptr; }
    }
    if (rotation_str != nullptr)
    {
        object->rotation() = glm::radians(parse_vector3(rotation_str));
        if (status() != Status::Success) { return nullptr; }
    }
    if (parent != nullptr)
    {
        parent->add_child(*object);
    }
    else
    {
        configuration_.scene->add_object(*object);
        object->update();
    }
    return object;
}

void XMLConfigurationLoader::parse_lights(const Element* source)
{
    if (!require_has_child(source, ELEMENT_LIGHT)) { return; }
    const std::vector<const char*> required_attributes
    { 
        ATTRIBUTE_TYPE,
        ATTRIBUTE_COLOR, ATTRIBUTE_INTENSITY
    };
    const Element* child = source->FirstChildElement(ELEMENT_LIGHT);
    while (child != nullptr)
    {
        if (!require_has_attributes(child, required_attributes)) { return; }
        const char* type = child->Attribute(ATTRIBUTE_TYPE);
        
        Light* light = nullptr;
        if (strcmp(type, VALUE_SPHERE) == 0)
        {
            light = parse_light_sphere(child);
        }
        else
        {
            status_ = Status::ParsingError;
            status_message_ = "Unknown light type: " + string(type);
        }
        if (status() != Status::Success) { return; }
        
        configuration_.lights.push_back(LightPtr(light));
        configuration_.scene->add_light(*light);
        light->update();

        child = child->NextSiblingElement(ELEMENT_LIGHT);
    }
}
Light* XMLConfigurationLoader::parse_light_sphere(const Element* source)
{
    const char* color_str = source->Attribute(ATTRIBUTE_COLOR);
    const Vector3 color = parse_vector3(color_str);
    if (status() != Status::Success) { return nullptr; }
    const float intensity = source->FloatAttribute(ATTRIBUTE_INTENSITY);
    
    Light* light = new SphereLight(color, intensity);

    const char* translation_str = source->Attribute(ATTRIBUTE_TRANSLATION);
    const char* scale_str = source->Attribute(ATTRIBUTE_SCALE);
    const char* rotation_str = source->Attribute(ATTRIBUTE_ROTATION);

    if (translation_str != nullptr)
    {
        light->translation() = parse_vector3(translation_str);
        if (status() != Status::Success) { return nullptr; }
    }
    if (scale_str != nullptr)
    {
        light->scale() = parse_vector3(scale_str);
        if (status() != Status::Success) { return nullptr; }
    }
    if (rotation_str != nullptr)
    {
        light->rotation() = glm::radians(parse_vector3(rotation_str));
        if (status() != Status::Success) { return nullptr; }
    }
    return light;
}

void XMLConfigurationLoader::parse_sampler(const Element* source)
{
    if (source == nullptr)
    {
        configuration_.sampler = SamplerPtr(new NaiveSampler());
        return;
    }
    if (!require_has_attributes(source, {ATTRIBUTE_TYPE})) { return; }
    
    const char* type = source->Attribute(ATTRIBUTE_TYPE);
    if (strcmp(type, VALUE_NAIVE) == 0)
    {
        configuration_.sampler = SamplerPtr(new NaiveSampler());
    }
    else if (strcmp(type, VALUE_RANDOM) == 0)
    {
        const int degree = source->IntAttribute(ATTRIBUTE_DEGREE);
        if (degree <= 0)
        {
            status_ = Status::ParsingError;
            status_message_ = "Sampler degree is <= 0";
            return;
        }
        configuration_.sampler = SamplerPtr(new RandomSampler(degree));
    }
    else if (strcmp(type, VALUE_JITTER) == 0)
    {
        const int degree = source->IntAttribute(ATTRIBUTE_DEGREE);
        if (degree <= 0)
        {
            status_ = Status::ParsingError;
            status_message_ = "Sampler degree is <= 0";
            return;
        }
        configuration_.sampler = SamplerPtr(new JitterSampler(degree));
    }
    else
    {
        status_ = Status::ParsingError;
        status_message_ = "Unknown sampler type: " + string(type);
    }
}
void XMLConfigurationLoader::parse_tracer(const Element* source)
{
    if (source == nullptr)
    {
        configuration_.tracer = TracerPtr(new NaiveTracer());
        return;
    }
    if (!require_has_attributes(source, {ATTRIBUTE_TYPE})) { return; }
    
    const char* type = source->Attribute(ATTRIBUTE_TYPE);
    if (strcmp(type, VALUE_NAIVE) == 0)
    {
        configuration_.tracer = TracerPtr(new NaiveTracer());
    }
    else if (strcmp(type, VALUE_PATH) == 0)
    {
        const int degree = source->IntAttribute(ATTRIBUTE_DEGREE);
        if (degree <= 0)
        {
            status_ = Status::ParsingError;
            status_message_ = "Tracer degree is <= 0";
            return;
        }
        configuration_.tracer = TracerPtr(new PathTracer(degree));
    }
    else
    {
        status_ = Status::ParsingError;
        status_message_ = "Unknown tracer type: " + string(type);
    }
}
void XMLConfigurationLoader::parse_camera(const Element* source)
{
    if (source == nullptr) { return; }
    
    const float fov = glm::radians(source->FloatAttribute(ATTRIBUTE_FOV));
    const float aspect = source->FloatAttribute(ATTRIBUTE_ASPECT);
    const float near = source->FloatAttribute(ATTRIBUTE_NEAR);
    const float far = source->FloatAttribute(ATTRIBUTE_FAR);
    
    configuration_.camera = Camera(fov, aspect, near, far);

    const char* translation = source->Attribute(ATTRIBUTE_TRANSLATION);
    if (translation != nullptr)
    {
        configuration_.camera.translation() = parse_vector3(translation);
        if (status() != Status::Success) { return; }
    }
    const char* look_at = source->Attribute(ATTRIBUTE_LOOK_AT);
    if (look_at != nullptr)
    {
        configuration_.camera.look_at(parse_vector3(look_at));
        if (status() != Status::Success) { return; }
    }
    configuration_.camera.update();
}
void XMLConfigurationLoader::parse_image(const Element* source)
{
    if (source == nullptr) { return; }

    const int width = source->IntAttribute(ATTRIBUTE_WIDTH);
    const int height = source->IntAttribute(ATTRIBUTE_HEIGHT);
    if (width <= 0 || height <= 0)
    {
        status_ = Status::ParsingError;
        status_message_ = "Image width/height is <= 0";
        return;
    }
    configuration_.image_size = Vector2u(width, height);

    const char* path = source->Attribute(ATTRIBUTE_PATH);
    if (path != nullptr)
    {
        configuration_.image_path = path;
    }
}

Vector3 XMLConfigurationLoader::parse_color(const char* str)
{
    Vector3 result;
    if (str[0] == HEX_SYMBOL)
    {
        std::stringstream ss;
        int hex_value;
        ss << std::hex << &str[1];
        ss >> hex_value;
        result = color::from_hex(hex_value);
    }
    else
    {
        status_ = Status::ParsingError;
        status_message_ = "Unknown color: " + std::string(str);
    }
    return result;
}
Vector3 XMLConfigurationLoader::parse_vector3(const char* str)
{
    Vector3 result;

    std::vector<string> components = split(str, DELIMETER);
    if (components.size() != 3)
    {
        status_ = Status::ParsingError;
        status_message_ = "Expected exactly 3 components for vector: " +
                           string(str);
        return result;
    }
    else
    {
        result.x = std::stof(components.at(0));
        result.y = std::stof(components.at(1));
        result.z = std::stof(components.at(2));
    }
    return result;
}

#include <iris/XMLSceneReader.h>

#include <iris/LambertMaterial.h>

#include <iris/Geometry.h>
#include <iris/PlaneGeometry.h>
#include <iris/SphereGeometry.h>

#include <iris/Scene.h>

#include <iris/color.h>
#include <iris/string.h>

#include <queue>
#include <sstream>


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
using std::string;


const char* XMLSceneReader::ELEMENT_CONFIGURATION = "configuration";
const char* XMLSceneReader::ELEMENT_MATERIALS = "materials";
const char* XMLSceneReader::ELEMENT_MATERIAL = "material";
const char* XMLSceneReader::ELEMENT_TEXTURES = "textures";
const char* XMLSceneReader::ELEMENT_TEXTURE = "texture";
const char* XMLSceneReader::ELEMENT_GEOMETRIES = "geometries";
const char* XMLSceneReader::ELEMENT_GEOMETRY = "geometry";
const char* XMLSceneReader::ELEMENT_SCENE = "scene";
const char* XMLSceneReader::ELEMENT_OBJECTS = "objects";
const char* XMLSceneReader::ELEMENT_OBJECT = "object";
const char* XMLSceneReader::ELEMENT_LIGHTS = "lights";
const char* XMLSceneReader::ELEMENT_LIGHT = "light";

const char* XMLSceneReader::ATTRIBUTE_NAME = "name";
const char* XMLSceneReader::ATTRIBUTE_TYPE = "type";
const char* XMLSceneReader::ATTRIBUTE_WIDTH = "width";
const char* XMLSceneReader::ATTRIBUTE_HEIGHT = "height";
const char* XMLSceneReader::ATTRIBUTE_ALBEDO = "albedo";
const char* XMLSceneReader::ATTRIBUTE_PATTERN = "pattern";
const char* XMLSceneReader::ATTRIBUTE_TEXTURE_SCALE_X = "textureScaleU";
const char* XMLSceneReader::ATTRIBUTE_TEXTURE_SCALE_Y = "textureScaleV";
const char* XMLSceneReader::ATTRIBUTE_GEOMETRY = "geometry";
const char* XMLSceneReader::ATTRIBUTE_TEXTURE = "texture";
const char* XMLSceneReader::ATTRIBUTE_TRANSLATION = "translation";
const char* XMLSceneReader::ATTRIBUTE_SCALE = "scale";
const char* XMLSceneReader::ATTRIBUTE_ROTATION = "rotation";

const char* XMLSceneReader::VALUE_LAMBERT = "lambert";
const char* XMLSceneReader::VALUE_PLANE = "plane";
const char* XMLSceneReader::VALUE_SPHERE = "sphere";

const char XMLSceneReader::HEX_SYMBOL = '#';

const char XMLSceneReader::DELIMETER = ',';

Configuration XMLSceneReader::read_from_path(const std::string& path)
{
    // TODO
    return read_from_string(path);
}
Configuration XMLSceneReader::read_from_string(const std::string& xml)
{
    configuration_ = Configuration();
    
    status_ = Status::Success;
    status_message_ = "";

    XMLDocument doc;
    auto s = std::string(xml.c_str());
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

bool XMLSceneReader::require_has_child
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
bool XMLSceneReader::require_has_attributes
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

void XMLSceneReader::parse_configuration(const Element* source)
{
    if (!require_has_child(source, ELEMENT_MATERIALS) ||
        !require_has_child(source, ELEMENT_TEXTURES) ||
        !require_has_child(source, ELEMENT_GEOMETRIES) ||
        !require_has_child(source, ELEMENT_SCENE))
    {
        return;
    }
    parse_materials(source->FirstChildElement(ELEMENT_MATERIALS));
    if (status() != Status::Success) { return; }
    parse_textures(source->FirstChildElement(ELEMENT_TEXTURES));
    if (status() != Status::Success) { return; }
    parse_geometries(source->FirstChildElement(ELEMENT_GEOMETRIES));
    if (status() != Status::Success) { return; }
    parse_scene(source->FirstChildElement(ELEMENT_SCENE));
    if (status() != Status::Success) { return; }
}

void XMLSceneReader::parse_materials(const Element* source)
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
Material* XMLSceneReader::parse_material_lambert(const Element* source)
{
    if (!require_has_attributes(source, {ATTRIBUTE_ALBEDO})) { return nullptr; }

    const char* albedo_str = source->Attribute(ATTRIBUTE_ALBEDO);
    const Vector3 albedo = parse_color(albedo_str);
    return new LambertMaterial(albedo);
}

void XMLSceneReader::parse_textures(const Element* source)
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
Texture* XMLSceneReader::parse_texture(const Element* source)
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

void XMLSceneReader::parse_geometries(const Element* source)
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
Geometry* XMLSceneReader::parse_geometry_plane(const Element* source)
{
    const float texture_scale_x = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_X);
    const float texture_scale_y = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_Y);
    if (texture_scale_x <= 0 || texture_scale_y <= 0)
    {
        status_ = Status::ParsingError;
        status_message_ = "Texture scale is <= 0";
        return nullptr;
    }
    return new PlaneGeometry(texture_scale_x, texture_scale_y);
}
Geometry* XMLSceneReader::parse_geometry_sphere(const Element* source)
{
    const float texture_scale_x = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_X);
    const float texture_scale_y = source->FloatAttribute(ATTRIBUTE_TEXTURE_SCALE_Y);
    if (texture_scale_x <= 0 || texture_scale_y <= 0)
    {
        status_ = Status::ParsingError;
        status_message_ = "Texture scale is <= 0";
        return nullptr;
    }
    return new SphereGeometry(texture_scale_x, texture_scale_y);
}

void XMLSceneReader::parse_scene(const Element* source)
{
    if (!require_has_child(source, ELEMENT_OBJECTS) ||
        !require_has_child(source, ELEMENT_LIGHTS))
    {
        return;
    }
    configuration_.scene = ScenePtr(new Scene());
    parse_objects(source->FirstChildElement(ELEMENT_OBJECTS), nullptr);
    if (status() != Status::Success) { return; }
}
void XMLSceneReader::parse_objects(const Element* source, Object3D* parent)
{
    if (!require_has_child(source, ELEMENT_OBJECT)) { return; }
    const Element* child = source->FirstChildElement(ELEMENT_OBJECT);
    while (child != nullptr)
    {
        parse_object(child, parent);
        if (status() != Status::Success) { return; }
        child = child->NextSiblingElement(ELEMENT_OBJECT);
    }
}
Object3D* XMLSceneReader::parse_object(const Element* source, Object3D* parent)
{
    const char* translation_str = source->Attribute(ATTRIBUTE_TRANSLATION);
    const char* scale_str = source->Attribute(ATTRIBUTE_SCALE);
    const char* rotation_str = source->Attribute(ATTRIBUTE_ROTATION);

    const char* texture_str = source->Attribute(ATTRIBUTE_TEXTURE);
    const char* geometry_str = source->Attribute(ATTRIBUTE_GEOMETRY);

    ObjectPtr object = nullptr;
    if (geometry_str != nullptr && texture_str != nullptr)
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
        object = ObjectPtr(new Object3D
        (
            *configuration_.geometries[geometry_str], 
            *configuration_.textures[texture_str]
        ));
    }
    else
    {
        object = ObjectPtr(new Object3D());
        parse_objects(source, object.get());
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
        object->rotation() = parse_vector3(rotation_str);
        if (status() != Status::Success) { return nullptr; }
    }
    if (parent != nullptr)
    {
        parent->add_child(*object);
    }
    else
    {
        configuration_.scene->add_object(*object);
    }
    configuration_.objects.push_back(object);
    return object.get();
}

Vector3 XMLSceneReader::parse_color(const char* str)
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
Vector3 XMLSceneReader::parse_vector3(const char* str)
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

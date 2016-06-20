#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/XMLSceneReader.h>
#include <iris/LambertMaterial.h>
#include <iris/PlaneGeometry.h>
#include <iris/SphereGeometry.h>
#include <iris/Object3D.h>
#include <iris/NaiveSampler.h>
#include <iris/RandomSampler.h>
#include <iris/JitterSampler.h>
#include <iris/NaiveTracer.h>
#include <iris/PathTracer.h>
#include <iris/color.h>

#include <iostream>

using namespace iris;
using Status = SceneReader::Status;


template <typename T>
const T* get_material(const Configuration& config, const std::string& name)
{
    return dynamic_cast<const T*>
    (
        config.materials.at(name).get()
    );
}
template <typename T>
const T* get_geometry(const Configuration& config, const std::string& name)
{
    return dynamic_cast<const T*>
    (
        config.geometries.at(name).get()
    );
}

TEST_CASE("xml scene reader", "[scene-reader][xml-scene-reader]")
{
    XMLSceneReader reader;

    SECTION("materials")
    {
        const std::string xml = 
            "<configuration>"
	            "<materials>"
		            "<material name='white' type='lambert'" 
		                      "albedo='#FFFFFF'/>"
		            "<material name='black' type='lambert'"
		                      "albedo='#000000'/>"
	            "</materials>"
            "</configuration>";
        const Configuration config = reader.read_from_string(xml);
        
        REQUIRE(reader.status() == Status::Success);
        
        REQUIRE(config.materials.size() == 2);
        
        auto m_white = get_material<LambertMaterial>(config, "white");
        REQUIRE(m_white != nullptr);
        REQUIRE(m_white->albedo() == color::from_hex(0xFFFFFF));

        auto m_black = get_material<LambertMaterial>(config, "black");
        REQUIRE(m_black != nullptr);
        REQUIRE(m_black->albedo() == color::from_hex(0x000000));
    }
    SECTION("textures")
    {
        const std::string xml = 
            "<configuration>"
	            "<materials>"
		            "<material name='white' type='lambert'" 
		                      "albedo='#FFFFFF'/>"
		            "<material name='black' type='lambert'"
		                      "albedo='#000000'/>"
	            "</materials>"
                "<textures>"
                    "<texture name='white'"
                             "width='1' height='1'"
                             "pattern='white' />"
                    "<texture name='black'"
                             "width='1' height='1'"
                             "pattern='black' />"
                "</textures>"
            "</configuration>";
        const Configuration config = reader.read_from_string(xml);
        
        REQUIRE(reader.status() == Status::Success);

        REQUIRE(config.materials.size() == 2);
        auto m_white = get_material<LambertMaterial>(config, "white");
        REQUIRE(m_white != nullptr);
        auto m_black = get_material<LambertMaterial>(config, "black");
        REQUIRE(m_black != nullptr);

        REQUIRE(config.textures.size() == 2);

        auto t_white = config.textures.at("white").get();
        REQUIRE(t_white != nullptr);
        REQUIRE(t_white->resolution() == Vector2u(1, 1));
        REQUIRE(&t_white->sample(0.5f, 0.5f) == m_white);
        
        auto t_black = config.textures.at("black").get();
        REQUIRE(t_black != nullptr);
        REQUIRE(t_black->resolution() == Vector2u(1, 1));
        REQUIRE(&t_black->sample(0.5f, 0.5f) == m_black);
    }
    SECTION("geometries")
    {
        const std::string xml = 
            "<configuration>"
                "<geometries>"
		            "<geometry name='plane' type='plane'" 
		                      "textureScaleU='0.1' textureScaleV='0.2' />"
                    "<geometry name='sphere' type='sphere'" 
		                      "textureScaleU='0.3' textureScaleV='0.4' />"
	            "</geometries>"
            "</configuration>";
        const Configuration config = reader.read_from_string(xml);
        
        REQUIRE(reader.status() == Status::Success);

        REQUIRE(config.geometries.size() == 2);

        auto g_plane = get_geometry<PlaneGeometry>(config, "plane");
        REQUIRE(g_plane != nullptr);
        REQUIRE(g_plane->texture_scale() == Vector2(0.1f, 0.2f));
        
        auto g_sphere = get_geometry<SphereGeometry>(config, "sphere");
        REQUIRE(g_sphere != nullptr);
        REQUIRE(g_sphere->texture_scale() == Vector2(0.3f, 0.4f));
    }
    SECTION("scene")
    {
        const std::string xml = 
            "<configuration>"
	            "<materials>"
		            "<material name='white' type='lambert'" 
		                      "albedo='#FFFFFF'/>"
		            "<material name='black' type='lambert'"
		                      "albedo='#000000'/>"
	            "</materials>"
                "<textures>"
                    "<texture name='white'"
                             "width='1' height='1'"
                             "pattern='white' />"
                    "<texture name='black'"
                             "width='1' height='1'"
                             "pattern='black' />"
                "</textures>"
                "<geometries>"
		            "<geometry name='plane' type='plane'" 
		                      "textureScaleU='0.1' textureScaleV='0.2' />"
                    "<geometry name='sphere' type='sphere'" 
		                      "textureScaleU='0.3' textureScaleV='0.4' />"
	            "</geometries>"
                "<scene>"
                    "<objects>"
                        "<object translation='1,2,3' scale='4,5,6' rotation='7,8,9'>"
                            "<object geometry='plane' texture='white' />"
                            "<object geometry='plane' texture='black' />"
                        "</object>"
                        "<object geometry='sphere' texture='white' />"
                    "</objects>"
                    "<lights>"
                        "<light type='sphere' color='0.1,0.2,0.3' intensity='1'" 
                                "translation='1,2,3' scale='4,5,6' rotation='7,8,9' />"
                        "<light type='sphere' color='0.4,0.5,0.6' intensity='2'" 
                                "translation='9,8,7' scale='6,5,4' rotation='3,2,1' />"
                    "</lights>"
                "</scene>"
            "</configuration>";
            
        const Configuration config = reader.read_from_string(xml);
        
        REQUIRE(reader.status() == Status::Success);

        REQUIRE(config.materials.size() == 2);
        auto m_white = get_material<LambertMaterial>(config, "white");
        REQUIRE(m_white != nullptr);
        auto m_black = get_material<LambertMaterial>(config, "black");
        REQUIRE(m_black != nullptr);

        REQUIRE(config.textures.size() == 2);
        auto t_white = config.textures.at("white").get();
        REQUIRE(t_white != nullptr);
        auto t_black = config.textures.at("black").get();
        REQUIRE(t_black != nullptr);

        REQUIRE(config.geometries.size() == 2);
        auto g_plane = get_geometry<PlaneGeometry>(config, "plane");
        REQUIRE(g_plane != nullptr);
        auto g_sphere = get_geometry<SphereGeometry>(config, "sphere");
        REQUIRE(g_sphere != nullptr);
        REQUIRE(config.scene != nullptr);

        REQUIRE(config.objects.size() == 4);
        REQUIRE(config.scene->object_count() == 2);

        const Object3D& o_planes = config.scene->object(0);
        REQUIRE(is_close(o_planes.translation(), Vector3(1, 2, 3)));
        REQUIRE(is_close(o_planes.scale(), Vector3(4, 5, 6)));
        REQUIRE(is_close(o_planes.rotation(), Vector3(7, 8, 9)));
        REQUIRE(o_planes.child_count() == 2);
        REQUIRE(o_planes.child(0).child_count() == 0);
        REQUIRE(o_planes.child(0).geometry() == *g_plane);
        REQUIRE(o_planes.child(0).texture() == *t_white);
        REQUIRE(o_planes.child(1).child_count() == 0);
        REQUIRE(o_planes.child(1).geometry() == *g_plane);
        REQUIRE(o_planes.child(1).texture() == *t_black);

        const Object3D& o_sphere = config.scene->object(1); 
        REQUIRE(o_sphere.child_count() == 0);
        REQUIRE(o_sphere.geometry() == *g_sphere);
        REQUIRE(o_sphere.texture() == *t_white);

        REQUIRE(config.lights.size() == 2);
        REQUIRE(config.scene->light_count() == 2);

        const Light& light_a = config.scene->light(0);
        REQUIRE(is_close(light_a.color(), Vector3(0.1, 0.2, 0.3)));
        REQUIRE(light_a.intensity() == 1.0f);
        REQUIRE(is_close(light_a.translation(), Vector3(1, 2, 3)));
        REQUIRE(is_close(light_a.scale(), Vector3(4, 5, 6)));
        REQUIRE(is_close(light_a.rotation(), Vector3(7, 8, 9)));
        
        const Light& light_b = config.scene->light(1); 
        REQUIRE(is_close(light_b.color(), Vector3(0.4, 0.5, 0.6)));
        REQUIRE(light_b.intensity() == 2.0f);
        REQUIRE(is_close(light_b.translation(), Vector3(9, 8, 7)));
        REQUIRE(is_close(light_b.scale(), Vector3(6, 5, 4)));
        REQUIRE(is_close(light_b.rotation(), Vector3(3, 2, 1)));
    }
    SECTION("sampler")
    {
        const std::string xml_naive = 
            "<configuration>"
                "<sampler type='naive' />"
            "</configuration>";
        const std::string xml_random = 
            "<configuration>"
                "<sampler type='random' degree='2' />"
            "</configuration>";
        const std::string xml_jitter = 
            "<configuration>"
                "<sampler type='jitter' degree='3' />"
            "</configuration>";

        const Configuration config_naive = reader.read_from_string(xml_naive);
        REQUIRE(reader.status() == Status::Success);
        auto sampler_naive = dynamic_cast<const NaiveSampler*>(config_naive.sampler.get());  
        REQUIRE(sampler_naive != nullptr);

        const Configuration config_random = reader.read_from_string(xml_random);
        REQUIRE(reader.status() == Status::Success);
        auto sampler_random = dynamic_cast<const RandomSampler*>(config_random.sampler.get());  
        REQUIRE(sampler_random != nullptr);
        REQUIRE(sampler_random->sample_count() == 2);

        const Configuration config_jitter = reader.read_from_string(xml_jitter);
        REQUIRE(reader.status() == Status::Success);
        auto sampler_jitter = dynamic_cast<const JitterSampler*>(config_jitter.sampler.get());  
        REQUIRE(sampler_jitter != nullptr);
        REQUIRE(sampler_jitter->degree() == 3);
    }
    SECTION("tracer")
    {
        const std::string xml_naive = 
            "<configuration>"
                "<tracer type='naive' />"
            "</configuration>";
        const std::string xml_path = 
            "<configuration>"
                "<tracer type='path' degree='2' />"
            "</configuration>";

        const Configuration config_naive = reader.read_from_string(xml_naive);
        REQUIRE(reader.status() == Status::Success);
        auto tracer_naive = dynamic_cast<const NaiveTracer*>(config_naive.tracer.get());  
        REQUIRE(tracer_naive != nullptr);

        const Configuration config_random = reader.read_from_string(xml_path);
        REQUIRE(reader.status() == Status::Success);
        auto tracer_path = dynamic_cast<const PathTracer*>(config_random.tracer.get());  
        REQUIRE(tracer_path != nullptr);
        REQUIRE(tracer_path->max_depth() == 2);
    }
    SECTION("camera")
    {
        const std::string xml = 
            "<configuration>"
                "<camera fov='75' aspect='1' near='0.1' far='10'"
                        "translation='1,2,3' lookAt='4,5,6' />"
            "</configuration>";

        const Configuration config = reader.read_from_string(xml);
        REQUIRE(reader.status() == Status::Success);
        REQUIRE(config.camera.fov() == glm::radians(75.0f));
        REQUIRE(config.camera.aspect() == 1);
        REQUIRE(config.camera.near() == 0.1f);
        REQUIRE(config.camera.far() == 10);
        REQUIRE(is_close(config.camera.translation(), Vector3(1, 2, 3)));
        REQUIRE(is_close(config.camera.target(), Vector3(4, 5, 6)));
    }
    SECTION("image")
    {
        const std::string xml = 
            "<configuration>"
                "<image width='1' height='2' path='hello world' />"
            "</configuration>";

        const Configuration config = reader.read_from_string(xml);
        REQUIRE(reader.status() == Status::Success);
        REQUIRE(config.image_size == Vector2u(1, 2));
        REQUIRE(config.image_path == "hello world");
    }
}

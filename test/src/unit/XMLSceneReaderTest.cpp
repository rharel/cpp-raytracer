#include "../../lib/catch.hpp"

#include "../helpers.h"

#include <iris/XMLSceneReader.h>
#include <iris/LambertMaterial.h>
#include <iris/PlaneGeometry.h>
#include <iris/SphereGeometry.h>
#include <iris/Object3D.h>
#include <iris/color.h>

#include <iostream>

using namespace iris;
using Status = SceneReader::Status;


template <typename T>
const T* get_material(const Configuration& info, const std::string& name)
{
    return dynamic_cast<const T*>
    (
        info.materials.at(name).get()
    );
}
template <typename T>
const T* get_geometry(const Configuration& info, const std::string& name)
{
    return dynamic_cast<const T*>
    (
        info.geometries.at(name).get()
    );
}

TEST_CASE("xml scene reader", "[scene-reader][xml-scene-reader]")
{
    const std::string bad_config = "@!@#";
    const std::string config = 
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
                "<light type='sphere'" 
                        "translation='1,2,3' scale='4,5,6' rotation='7,8,9' />"
                "<light type='sphere'" 
                        "translation='9,8,7' scale='6,5,4' rotation='3,2,1' />"
            "</lights>"
        "</scene>"
    "</configuration>";

    XMLSceneReader reader;

    reader.read_from_string(bad_config);
    REQUIRE(reader.status() == Status::ParsingError);

    const Configuration info = reader.read_from_string(config);
    std::cout << reader.status_message() << std::endl;
    REQUIRE(reader.status() == Status::Success);

    // materials //

    REQUIRE(info.materials.size() == 2);
    auto m_white = get_material<LambertMaterial>(info, "white");
    auto m_black = get_material<LambertMaterial>(info, "black");
    REQUIRE(m_white != nullptr);
    REQUIRE(m_black != nullptr);
    REQUIRE(m_white->albedo() == color::from_hex(0xFFFFFF));
    REQUIRE(m_black->albedo() == color::from_hex(0x000000));

    // textures //

    REQUIRE(info.textures.size() == 2);
    auto t_white = info.textures.at("white").get();
    auto t_black = info.textures.at("black").get();
    REQUIRE(t_white != nullptr);
    REQUIRE(t_black != nullptr);
    REQUIRE(t_white->resolution() == Vector2u(1, 1));
    REQUIRE(t_black->resolution() == Vector2u(1, 1));
    REQUIRE(&t_white->sample(0.5f, 0.5f) == m_white);
    REQUIRE(&t_black->sample(0.5f, 0.5f) == m_black);

    // geometries //

    REQUIRE(info.geometries.size() == 2);
    auto g_plane = get_geometry<PlaneGeometry>(info, "plane");
    auto g_sphere = get_geometry<SphereGeometry>(info, "sphere");
    REQUIRE(g_plane != nullptr);
    REQUIRE(g_sphere != nullptr);
    REQUIRE(g_plane->texture_scale() == Vector2(0.1f, 0.2f));
    REQUIRE(g_sphere->texture_scale() == Vector2(0.3f, 0.4f));

    // scene //

    std::cout << reader.status_message() << std::endl;
    REQUIRE(info.objects.size() == 4);
    REQUIRE(info.scene != nullptr);
    REQUIRE(info.scene->object_count() == 2);

    // scene objects //

    const Object3D& o_plane_host = info.scene->object(0);
    const Object3D& o_sphere = info.scene->object(1); 
    REQUIRE(is_close(o_plane_host.translation(), Vector3(1, 2, 3)));
    REQUIRE(is_close(o_plane_host.scale(), Vector3(4, 5, 6)));
    REQUIRE(is_close(o_plane_host.rotation(), Vector3(7, 8, 9)));
    REQUIRE(o_plane_host.child_count() == 2);
    REQUIRE(o_plane_host.child(0).child_count() == 0);
    REQUIRE(o_plane_host.child(0).geometry() == *g_plane);
    REQUIRE(o_plane_host.child(0).texture() == *t_white);
    REQUIRE(o_plane_host.child(1).child_count() == 0);
    REQUIRE(o_plane_host.child(1).geometry() == *g_plane);
    REQUIRE(o_plane_host.child(1).texture() == *t_black);
    REQUIRE(o_sphere.child_count() == 0);
    REQUIRE(o_sphere.geometry() == *g_sphere);
    REQUIRE(o_sphere.texture() == *t_white);

    // scene lights //
}

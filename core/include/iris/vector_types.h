#ifndef IRIS_VECTOR_TYPES_H
#define IRIS_VECTOR_TYPES_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Vector type definitions.
 */


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/quaternion.hpp>


namespace iris
{
    typedef glm::uvec2 Vector2u;
    typedef glm::uvec3 Vector3u;
    typedef glm::uvec4 Vector4u;

    typedef glm::ivec2 Vector2i;
    typedef glm::ivec3 Vector3i;
    typedef glm::ivec4 Vector4i;

    typedef glm::vec2 Vector2;
    typedef glm::vec3 Vector3;
    typedef glm::vec4 Vector4;

    typedef glm::quat Quaternion;
}



#endif  // IRIS_VECTOR_TYPES_H

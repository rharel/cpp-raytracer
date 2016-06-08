#ifndef IRIS_VECTOR_TYPES_H
#define IRIS_VECTOR_TYPES_H
/**
 * @file VectorTypes.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Vector type definitions.
 */


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


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
}



#endif  // IRIS_VECTOR_TYPES_H

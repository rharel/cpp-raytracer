#ifndef IRIS_H
#define IRIS_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Main header.
 */


#include <iris/Material.h>
#include <iris/LambertMaterial.h>
#include <iris/Texture.h>

#include <iris/Geometry.h>
#include <iris/PlaneGeometry.h>

#include <iris/Sampler.h>
#include <iris/NaiveSampler.h>
#include <iris/sample_aggregators.h>

#include <iris/Raytracer.h>
#include <iris/Pathtracer.h>

#include <iris/Scene.h>
#include <iris/Camera.h>

#include <iris/Image.h>
#include <iris/Composer.h>

#include <iris/math.h>
#include <iris/vector_types.h>
#include <iris/matrix_types.h>


#endif  // IRIS_H

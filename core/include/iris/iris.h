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
#include <iris/SphereGeometry.h>

#include <iris/Light.h>
#include <iris/SphereLight.h>

#include <iris/Sampler.h>
#include <iris/NaiveSampler.h>
#include <iris/RandomSampler.h>
#include <iris/JitterSampler.h>
#include <iris/AdaptiveSampler.h>

#include <iris/Raytracer.h>
#include <iris/NaiveTracer.h>
#include <iris/PathTracer.h>

#include <iris/Scene.h>
#include <iris/Camera.h>

#include <iris/Image.h>
#include <iris/Composer.h>

#include <iris/ConfigurationLoader.h>
#include <iris/XMLConfigurationLoader.h>

#include <iris/aggregators.h>
#include <iris/color.h>
#include <iris/math.h>
#include <iris/vector_types.h>
#include <iris/matrix_types.h>


#endif  // IRIS_H

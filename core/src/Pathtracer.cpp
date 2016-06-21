#include <iris/PathTracer.h>
#include <iris/ray_math.h>
#include <iris/math.h>
#include <iris/random.h>

#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/quaternion.hpp>


using namespace iris;
using namespace iris::constant;
using glm::clamp;
using glm::dot;
using glm::normalize;


PathTracer::PathTracer()
    : PathTracer(Vector3(0), 0) {}
PathTracer::PathTracer(const Vector3& horizon)
    : PathTracer(horizon, 0) {}
PathTracer::PathTracer(const size_t max_bounce_count)
    : PathTracer(Vector3(0), max_bounce_count) {}
PathTracer::PathTracer
(
    const Vector3& horizon, 
    const size_t max_bounce_count
)
    : horizon_(clamp(horizon, 0.0f, 1.0f)), 
      max_bounce_count_(max_bounce_count) {}

Vector3 PathTracer::trace(Ray ray, const Scene& scene) const
{
    Vector3 color(0);
    Vector3 weight(1);
    
    size_t bounce_count = 0;
    while ((max_bounce_count_ == 0 && glm::length2(weight) < 0.01f) ||
           (max_bounce_count_ > 0 && bounce_count < max_bounce_count_))
    {
        Raycast collision(ray); 
        scene.raycast(collision);

        if (!collision.hit())
        { 
            color += weight * horizon_; 
            break; 
        }

        const Vector3 x = collision.point();
        const Vector3& N = collision.normal();
        const Material& material = collision.material();
        const Vector3 Wi = -ray.direction();

        // direct illumination //
        const Vector3 Ld = illuminate(scene, x, N, material, Wi);
        color += weight * Ld;

        // russian roulette //
        const float P_bounce = glm::compAdd(material.brdf()) / 3.0f;
        if (random::real_in_range(0.0f, 1.0f) > P_bounce) { break; }
        weight /= P_bounce;

        // bounce ray //
        const Quaternion R = glm::rotation(N, Vector3(0, 1, 0));
        const Quaternion R_inv = glm::inverse(R);
        float pdf;
        const Vector3 Wo = R_inv * material.bounce(R * Wi, pdf);
        const Vector3 f = material.brdf(R * Wi, R * Wo);
        const float cos_theta = dot(Wi, N);
        weight *= f * cos_theta / pdf;
        ray = Ray(x, Wo);

        ++ bounce_count;
    }
    return clamp(color, 0.0f, 1.0f);
}
Vector3 PathTracer::illuminate
(
    const Scene& scene,
    const Vector3& x,
    const Vector3& Nx,
    const Material& material,
    const Vector3& Wi
) const
{
    const size_t light_index = random::int_in_range<size_t>
    (
        0, 
        scene.light_count() - 1
    );
    const Light& light = scene.light(light_index);
    Vector3 y, Ny;
    light.random_on_surface(y, Ny);

    if (!scene.is_visible(x, y)) { return Vector3(0); }

    const Vector3 L = light.color() * light.intensity();
    const Vector3 Wo = normalize(y - x);

    const Quaternion R = glm::rotation(Nx, Vector3(0, 1, 0));
    const Vector3 f = material.brdf(R * Wi, R * Wo);
    const float G = form_factor(x, Nx, y, Ny);
    const float A = light.surface_area();

    return f * L * G * A;
}

const Vector3& PathTracer::horizon() const
{
    return horizon_;
}
size_t PathTracer::max_bounce_count() const
{
    return max_bounce_count_;
}

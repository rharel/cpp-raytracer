#include <iris/Composer.h>
#include <iris/aggregators.h>

#include <vector>


using namespace iris;


NaiveSampler Composer::default_sampler;
UniformAggregator Composer::default_aggregator;
PathTracer Composer::default_tracer(3);

Composer::Composer
(
    const size_t width, const size_t height,
    const Scene& scene, const Camera& camera
)
    : Composer
(
    width, height, 
    scene, camera, 
    default_sampler, default_aggregator, 
    default_tracer
) {}

Composer::Composer
(
    const size_t width, const size_t height,
    const Scene& scene, const Camera& camera,
    Sampler& sampler, const Aggregator& aggregator,
    const Raytracer& tracer
)
    : image_(width, height), 
      scene_(&scene), camera_(&camera), 
      sampler_(&sampler), aggregator_(&aggregator),
      tracer_(&tracer) {}

void Composer::render()
{
    for (size_t x = 0; x < image().width(); ++x)
    {
        for (size_t y = 0; y < image().height(); ++y)
        {
            render_pixel(x, y);
        }
    }
}
void Composer::render_pixel
(
    const size_t x, 
    const size_t y
)
{   
    const Vector2 origin(x, y);
    std::vector<Vector2> samples;
    std::vector<Vector3> colors;

    sampler_->reset();
    while (sampler_->has_next())
    {
        const Vector2 sample = sampler_->next();
        const Vector2 target = origin + sample;
        const Ray ray = ray_through(target.x, target.y);
        const Vector3 color = tracer_->trace(ray, *scene_);
        sampler_->report(color);

        samples.push_back(sample);
        colors.push_back(color);
    }

    const Vector3 average = aggregator_->operator()
    (
        &colors[0], &samples[0], 
        colors.size()
    );
    image_.pixel(x, y, average);
}
Ray Composer::ray_through(const float x, const float y) const
{
    // Pixel in normalized window space
    const Vector2 pn
    (
        x / static_cast<float>(image().width()),
        y / static_cast<float>(image().height())
    );
    // Pixel in camera space
    const Vector3 pc = camera_->on_near(pn.x, pn.y);
    // Pixel in world space
    const Vector3 p(camera_->view_matrix() * Vector4(pc, 1));

    // Ray origin in world space
    const Vector3 o = camera_->position();
    // Ray direction in world space
    const Vector3 D = p - o;

    return Ray(o, D);
}

const Image& Composer::image() const
{
    return image_;
}

#include <iris/Composer.h>

#include <vector>


using namespace iris;


NaiveSampler Composer::default_sampler;
UniformAggregator Composer::default_aggregator;
PathTracer Composer::default_tracer;

Composer::Composer
(
    const Scene& scene, 
    const Camera& camera,
    const Vector2u& image_size
)
    : Composer
(
    scene, camera, image_size, 
    default_sampler,  
    default_tracer, 
    default_aggregator
) {}

Composer::Composer
(
    const Scene& scene, 
    const Camera& camera,
    const Vector2u& image_size,
    Sampler& sampler, 
    const Raytracer& tracer,
    const Aggregator& aggregator
)
    : scene_(&scene), camera_(&camera), 
      image_(image_size.x, image_size.y),  
      sampler_(&sampler), 
      tracer_(&tracer),
      aggregator_(&aggregator) {}

void Composer::render()
{
    render(Vector2u(0, 0), 0);
}
Vector2u Composer::render
(
    const Vector2u& offset, 
    const size_t count
)
{
    const size_t w = image().width();
    const size_t h = image().height();
    size_t x = offset.x;
    size_t y = offset.y;
    size_t i = 0;
    while (y < h && (count == 0 || i < count))
    {
        render_pixel(x, y);
        ++i;
        
        ++x;
        if (x == w) { x = 0; ++y; }
    }
    return Vector2u(x, y);
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
    const Vector3 average_color = aggregator_->operator()
    (
        &colors[0], &samples[0], 
        colors.size()
    );
    image_.color_pixel(x, y, average_color);
}
Ray Composer::ray_through
(
    const float x, 
    const float y
) const
{
    // Pixel in normalized window space
    const Vector2 Pn
    (
        x / static_cast<float>(image().width()),
        y / static_cast<float>(image().height())
    );
    // Pixel in camera space
    const Vector3 Pc = camera_->on_near(Pn.x, Pn.y);
    // Pixel in world space
    const Vector3 Pw(camera_->view_matrix() * Vector4(Pc, 1));

    // Ray origin in world space
    const Vector3 o = camera_->position();
    // Ray direction in world space
    const Vector3 D = Pw - o;

    return Ray(o, D);
}

const Image& Composer::image() const
{
    return image_;
}

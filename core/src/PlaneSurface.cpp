#include <iris/PlaneSurface.h>

#include <glm/geometric.hpp>


using namespace iris;
using glm::dot;


PlaneSurface::PlaneSurface()
    : PlaneSurface(Texture::null, Vector2(0, 0)) {}
PlaneSurface::PlaneSurface(

    const Texture& texture,
    const Vector2& texture_tile_size
)
    : Surface(texture), 
      texture_tile_size_(texture_tile_size) {}

void PlaneSurface::update()
{
    Surface::update();

    const Matrix4& W = global_transform();
    Matrix4 R = W;
    R[3] = Vector4(0, 0, 0, 1);
    
    anchor_ = Vector3(W[3]);
    normal_ = Vector3(R * Vector4(0, 1, 0, 1));
    normal_ = glm::normalize(normal_);
    U_ = Vector3(R * Vector4(1, 0, 0, 1));
    U_ = glm::normalize(U_);
    V_ = Vector3(R * Vector4(0, 0, 1, 1));
    V_ = glm::normalize(V_);
}
void PlaneSurface::raycast(Raycast& result) const
{
    const Ray& ray = result.ray();
    const Vector3& O = ray.origin();
    const Vector3& D = ray.direction();
    const Vector3& A = anchor();
    const Vector3& N = normal();

    const float ND = dot(N, D);
    if (ND >= 0.0f) { return; }
    
    const float t = dot(-N, O - A) / ND;
    
    const Vector3 P = ray.at(t);
    const Vector3 AP = P - A;
    const float u = dot(AP, U()) / texture_tile_size().x;
    const float v = dot(AP, V()) / texture_tile_size().y;
    const Material& material = texture().sample(u, v);

    result.contact(t, normal_, material);
}

const Vector2& PlaneSurface::texture_tile_size() const
{
    return texture_tile_size_;
}
const Vector3& PlaneSurface::anchor() const
{
    return anchor_;
}
const Vector3& PlaneSurface::normal() const
{
    return normal_;
}
const Vector3& PlaneSurface::U() const
{
    return U_;
}
const Vector3& PlaneSurface::V() const
{
    return V_;
}

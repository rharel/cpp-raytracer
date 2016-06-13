#ifndef IRIS_CAMERA_H
#define IRIS_CAMERA_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Camera class.
 */


#include <iris/matrix_types.h>
#include <iris/Object3D.h>
#include <iris/vector_types.h>


namespace iris
{
    /**
     * The camera is a special object which from which 
     * rays originate.
     */
    class Camera : public Object3D
    {
        public:
        /**
         * Creates default camera.
         */
        Camera();
        /**
         * Creates a camera with given parameters.
         *
         * @param fov    Field of view angle.
         * @param aspect View aspect-ratio.
         * @param near   Near view plane.
         * @param far    Far view plane.
         */
        Camera(float fov, float aspect, float near, float far);

        /**
         * Updates inner transformation of this and all children.
         */
        void update() override;

        /**
         * Transform pixel from normalized window space
         * to camera space.
         */
        Vector3 on_near(float x, float y) const;

        /**
         * Directs camera at target position.
         */
        void look_at(float x, float y, float z);
        /**
         * Directs camera at target position.
         */
        void look_at(const Vector3& target);
        
        /**
         * Checks if the camera has no look-at target assigned.
         */
        bool is_free() const;
        /**
         * Lets the camera's transform control the view direction.
         */
        void free();

        /**
         * Gets field of view.
         */
        float fov() const;
        /**
         * Gets view aspect ratio.
         */
        float aspect() const;
        /**
         * Gets near view plane.
         */
        float near() const;
        /**
         * Gets far view plane.
         */
        float far() const;
        /**
         * Gets position.
         */
        const Vector3& position() const;
        /**
         * Gets forward direction.
         */
        const Vector3& forward() const;
        /**
         * Gets up direction.
         */
        const Vector3& up() const;
        /**
         * Gets right direction.
         */
        const Vector3& right() const;
        /**
         * Gets look-at target.
         */
        const Vector3& target() const;
        /**
         * Gets view matrix.
         */
        const Matrix4& view_matrix() const;
        /**
         * Gets inverse view matrix.
         */
        const Matrix4& view_matrix_inverse() const;
        /**
         * Gets projection matrix.
         */
        const Matrix4& projection_matrix() const;
        /**
         * Gets inverse projection matrix.
         */
        const Matrix4& projection_matrix_inverse() const;

        private:
        float fov_, aspect_;
        float near_, far_;

        float w_, w2_;
        float h_, h2_;

        bool free_ = true;

        Vector3 position_ = Vector3(0);
        Vector3 forward_ = Vector3(0, 0, 1); 
        Vector3 up_ = Vector3(0, 1, 0);
        Vector3 right_ = Vector3(1, 0, 0);
        Vector3 target_ = Vector3(0);

        Matrix4 view_, view_inverse_;
        Matrix4 projection_, projection_inverse_;
    };
}


#endif  // IRIS_CAMERA_H

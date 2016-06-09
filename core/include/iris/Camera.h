#ifndef IRIS_CAMERA_H
#define IRIS_CAMERA_H
/**
 * @file Camera.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * Camera class.
 */


#include <iris/SceneComponent.h>


namespace iris
{
    /**
     * The camera is a special scene component which describes
     * from where rays originate and in what direction.
     */
    class Camera : public SceneComponent
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
         * Directs camera at target position.
         *
         * @note Only takes effect after a call to update().
         */
        void look_at(float x, float y, float z);
        /**
         * Directs camera at target position.
         *
         * @note Only takes effect after a call to update().
         */
        void look_at(const Vector3& target);
        
        /**
         * Checks if the camera has no look-at target assigned.
         */
        bool is_free() const;
        /**
         * Lets the camera's transform control the view direction.
         *
         * @note Only takes effect after a call to update().
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

        private:
        float fov_, aspect_;
        float near_, far_;

        bool free_ = true;

        Vector3 position_ = Vector3(0);
        Vector3 forward_ = Vector3(0, 0, 1); 
        Vector3 up_ = Vector3(0, 1, 0);
        Vector3 right_ = Vector3(1, 0, 0);
        Vector3 target_ = Vector3(0);
    };
}


#endif  // IRIS_CAMERA_H

#ifndef IRIS_SCENE_COMPONENT_H
#define IRIS_SCENE_COMPONENT_H
/**
 * @author Raoul Harel
 * @url github.com/rharel/cpp-raytracer
 *
 * Object3D class.
 */


#include <iris/matrix_types.h>
#include <iris/vector_types.h>

#include <unordered_set>


namespace iris
{
    /**
     * 3d objects are instances of textured geometry.
     */
    class Object3D
    {
        public:
        /**
         * Checks if target is a child of this.
         */
        bool has_child(Object3D& target) const;
        /**
         * Checks if target is a descendant of this.
         */
        bool has_descendant(Object3D& target) const;
        /**
         * Assigns target as a child of this.
         *
         * @returns False if target is already a descendant of this.
         */
        bool add_child(Object3D& target);
        /**
         * Unassigns target as a child.
         *
         * @returns False if target is not a child of this.
         */
        bool remove_child(Object3D& target);

        /**
         * Checks if parent exists.
         */
        bool has_parent() const;
        /**
         * Gets parent.
         */
        Object3D& parent();
        /**
         * Gets parent.
         */
        const Object3D& parent() const;
        
        /**
         * Gets child count.
         */
        size_t child_count() const;
        /**
         * Gets child at index.
         */
        Object3D& child(size_t index);
        /**
         * Gets child at index.
         */
        const Object3D& child(size_t index) const;

        /**
         * Gets/sets translation.
         */
        Vector3& translation();
        /**
         * Gets translation.
         */
        const Vector3& translation() const;
        /**
         * Gets/sets scale.
         */
        Vector3& scale();
        /**
         * Gets scale.
         */
        const Vector3& scale() const;
        /**
         * Gets/sets rotation.
         */
        Vector3& rotation();
        /**
         * Gets rotation.
         */
        const Vector3& rotation() const;
        /**
         * Gets local transform.
         */
        const Matrix4& local_matrix() const;
        /**
         * Gets local transform inverse.
         */
        const Matrix4& local_matrix_inverse() const;
        /**
         * Gets global transform.
         */
        const Matrix4& world_matrix() const;
        /**
         * Gets global transform inverse.
         */
        const Matrix4& world_matrix_inverse() const;

        /**
         * Updates transformation matrices of this and all descendants.
         */
        virtual void update();
        
        bool operator==(const Object3D& other) const;
        bool operator!=(const Object3D& other) const;

        private:
        Object3D* parent_ = nullptr;
        std::unordered_set<Object3D*> children_;

        Vector3 translation_ = Vector3(0);
        Vector3 scale_ = Vector3(1);
        Vector3 rotation_ = Vector3(0);
        Matrix4 local_matrix_ = Matrix4(1);
        Matrix4 local_matrix_inverse_ = Matrix4(1);
        Matrix4 world_matrix_ = Matrix4(1);
        Matrix4 world_matrix_inverse_ = Matrix4(1);
    };
}


#endif  // IRIS_SCENE_COMPONENT_H

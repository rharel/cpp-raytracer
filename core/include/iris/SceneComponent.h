#ifndef IRIS_SCENE_COMPONENT_H
#define IRIS_SCENE_COMPONENT_H
/**
 * @file SceneComponent.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * SceneComponent class.
 */


#include <iris/MatrixTypes.h>
#include <iris/VectorTypes.h>

#include <set>


namespace iris
{
    /**
     * Scene components are the nods of the DAG representing the
     * scene.
     */
    class SceneComponent
    {
        public:
        /**
         * Checks if give component is a child.
         */
        bool has_child(SceneComponent& target) const;
        /**
         * Assigns target component as a child.
         *
         * @returns False if child was already assigned to this.
         */
        bool add_child(SceneComponent& target);
        /**
         * Unassigns target component as a child.
         *
         * @returns False if child was never assigned to this.
         */
        bool remove_child(SceneComponent& target);

        /**
         * Checks if parent exists.
         */
        bool has_parent() const;
        /**
         * Gets parent component.
         */
        SceneComponent& parent();
        /**
         * Gets parent component.
         */
        const SceneComponent& parent() const;
        
        /**
         * Gets child count.
         */
        size_t child_count() const;
        /**
         * Gets child at index.
         */
        SceneComponent& child(size_t index);
        /**
         * Gets child at index.
         */
        const SceneComponent& child(size_t index) const;

        /**
         * Translates component.
         *
         * @note Will only take effect after a call to update()
         */
        void translate(float x, float y, float z);
        /**
         * Scales component.
         *
         * @note Will only take effect after a call to update()
         */
        void scale(float x, float y, float z);
        /**
         * Rotates component.
         *
         * @note Will only take effect after a call to update()
         */
        void rotate(float x, float y, float z);

        /**
         * Gets local transform.
         */
        const Matrix4& local_transform() const;
        /**
         * Gets global transform.
         */
        const Matrix4& global_transform() const;
        
        /**
         * Updates inner transformation of this and all children.
         */
        virtual void update();
        
        private:
        SceneComponent* parent_ = nullptr;
        std::set<SceneComponent*> children_;

        Vector3 translation_ = Vector3(0.0f);
        Vector3 scale_ = Vector3(1.0f);
        Vector3 rotation_ = Vector3(0.0f);
        Matrix4 local_transform_ = Matrix4(1.0f);
        Matrix4 global_transform_ = Matrix4(1.0f);
    };
}


#endif  // IRIS_SCENE_COMPONENT_H

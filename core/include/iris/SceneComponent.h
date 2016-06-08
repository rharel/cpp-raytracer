#ifndef IRIS_SCENE_COMPONENT_H
#define IRIS_SCENE_COMPONENT_H
/**
 * @file SceneComponent.h
 * @author Raoul Harel
 * @url github.com/rharel/cpp-pathtracer
 *
 * SceneComponent class.
 */


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

        private:
        SceneComponent* parent_ = nullptr;
        std::set<SceneComponent*> children_;
    };
}


#endif  // IRIS_SCENE_COMPONENT_H

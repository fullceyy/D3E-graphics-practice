#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"

class Node
{
    private:
        Node* m_Parent = nullptr;
        std::vector<Node*> m_Children {};
    public:
        Node();
        ~Node();

        glm::vec3 m_Pos;
        glm::vec3 m_Rot;
        float m_UniScale;

        Node* get_parent() const;
        const std::vector<Node*>& get_children() const { return m_Children; }

        void reset_parent();
        void add_child(Node* child);
        void remove_child(Node* child);

        glm::mat4 world_transform() const;
        glm::mat4 view_matrix() const;

};

/* If one of my nodes presumably holds a parent inside of it  */

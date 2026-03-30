#include "Node.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <iostream>

Node::Node()
: m_Pos(0.f), m_Rot(0.f), m_UniScale(1.f)
{
}

Node::~Node()
{
}

Node* Node::get_parent() const
{
    if(m_Parent)
        return m_Parent;

    std::cout << "No parent detected for Node: " << this << std::endl;
    return nullptr;
}

void Node::reset_parent()
{
    this->m_Parent = nullptr;
}

void Node::add_child(Node* child)
{
    if(child)
    {
        m_Children.push_back(child);
        child->m_Parent = this;
    }
}

void Node::remove_child(Node* child)
{
    std::vector<Node*>::iterator it = std::find(m_Children.begin(), m_Children.end(), child);
    if(it != m_Children.end())
    {
        (*it)->reset_parent();
        m_Children.erase(it);
    } else {
        std::cout << "Provided Node child was not found in the parent : " << this << std::endl;
    }
}

glm::mat4 Node::world_transform() const
{
    return m_Parent ? (glm::translate(glm::mat4(1.f), m_Pos) *
            glm::eulerAngleYXZ(m_Rot.y, m_Rot.x, m_Rot.z) *
            glm::scale(glm::mat4(1.f), glm::vec3(m_UniScale)) * m_Parent->world_transform())
    : (glm::translate(glm::mat4(1.f), m_Pos) *
            glm::eulerAngleYXZ(m_Rot.y, m_Rot.x, m_Rot.z) *
            glm::scale(glm::mat4(1.f), glm::vec3(m_UniScale)));
}

glm::mat4 Node::view_matrix() const
{
    return glm::inverse(world_transform());
}

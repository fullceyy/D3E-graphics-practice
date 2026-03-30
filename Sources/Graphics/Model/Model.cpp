#include "Model.hpp"
#include "../Mesh/Mesh.hpp"
#include "glm/ext.hpp"

Model::Model()
: m_Node(new Node())
{
}

Model::~Model()
{
    for(std::vector<Mesh*>::iterator it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
    {
        delete *it;
    }
    m_Meshes.clear();
}

void Model::load(Mesh* to_load)
{
    Bundle copy(to_load);
    m_Node->add_child(copy.m_Node);
    m_Bundles.push_back(copy);
}

void Model::prepare(Shader* shader)
{
    m_ModelLoc = glGetUniformLocation(shader->get_program(), "model");
    m_ViewLoc  = glGetUniformLocation(shader->get_program(), "view");
    m_ProjLoc  = glGetUniformLocation(shader->get_program(), "projection");
}

void Model::render(Shader* shader, glm::mat4 view)
{
    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f
    );

    shader->bind();
    for(auto& el : m_Bundles)
    {
        glUniformMatrix4fv(glGetUniformLocation(shader->get_program(), "model"), 1, GL_FALSE, &(el.m_Node)->world_transform()[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader->get_program(), "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader->get_program(), "projection"), 1, GL_FALSE, &projection[0][0]);
        el.m_Mesh->draw();
    }
}

Node* Model::get_bundle_node(Mesh* to_find)
{
    for(auto& el : m_Bundles)
    {
        if(el.m_Mesh == to_find)
        {
            return el.m_Node;
        }
    }
    return nullptr;
}

Node* Model::get_root_node() const
{
    return m_Node;
}

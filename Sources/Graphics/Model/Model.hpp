#pragma once
#include <vector>
#include "../Mesh/Mesh.hpp"
#include "../Node/Node.hpp"
#include "../Shader/Shader.hpp"

/*
 * What to rethink:
 *  If I happen to want a better memory efficiency, I have to add a way to make a geometry or put it simply MESH
 *  to be shareable. In the sense where you can reuse the values of the previously created cube mesh, without the need
 *  of going through process of mesh creation again. Making mesh more of a metadata rather than separate component.
 *
    Concept	  | What it stores	     |  When it’s created	     |  How it’s used
    ------------------------------------------------------------------------------------------------------
    Mesh	  | Vertex data,         |                           |
              | VAO, VBO, EBO	     |  Once, at load	         |  Shared by all objects
    -----------------------------------------------------------------------------------------------------
    Instance  | Model matrix, color, |                           |
              | per-object data	     |  Dynamically, at runtime	 |  Uploaded to GPU as instanced buffer
    -----------------------------------------------------------------------------------------------------
    Rendering | Draw call	         |  Every frame	             |  glDrawElementsInstanced reads mesh + instance buffer

    Important: You never duplicate the VBO for each cube. All runtime “copies” are just instance data, which is tiny compared to vertex buffers.
 */

struct Bundle
{
    Mesh* m_Mesh;
    Node* m_Node;

    Bundle(Mesh* mesh)
    : m_Mesh(mesh), m_Node(new Node())
    {
        mesh->setup();
    }
};

class Model
{
    private:
        // all the meshes listed here are bound by default to one NODE. Which is actually fucking stupid apparently yo
        std::vector<Mesh*> m_Meshes {};
        // Parent node to everyone in m_Bundles ?
        Node* m_Node;

        std::vector<struct Bundle> m_Bundles {};

        GLuint m_ModelLoc;
        GLuint m_ViewLoc;
        GLuint m_ProjLoc;
    public:
        Model();
        ~Model();

        void load(Mesh* to_load);
        void prepare(Shader* shader);
        void render(Shader* shader, glm::mat4 view);

        Node* get_bundle_node(Mesh* to_find);
        Node* get_root_node() const;
};

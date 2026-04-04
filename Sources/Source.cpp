#include "Core/Window/Window.hpp"
#include "Core/InputSystem/InputSystem.hpp"
// #include "Graphics/Mesh/VBO/VertexBufferObject.hpp"
#include "Graphics/Mesh/Vertex.hpp"
#include "Core/Renderer/RenderCommand.hpp"
#include "Core/Renderer/Renderer.hpp"
#include "Core/Renderer/FinalVertexArray.hpp"
#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Mesh/StaticMeshShapes/Cube.hpp"
#include "Core/Camera/Camera.hpp"

#include "ext/matrix_transform.hpp"
#include "glm/ext.hpp"
#include <iostream>

int main(void)
{
    // Camera* cam = new Camera(glm::vec3(0.f, 0.f, 5.f));
    // std::unique_ptr<Camera> cam = std::make_unique<Camera>(glm::vec3(0.f, 0.f, 5.f));
    D3E::Camera camera(glm::vec3(0.f, 0.f, 5.f));
    D3E::Window window;
    D3E::Renderer renderer;
    D3E::InputSystem input_system(window.get_window());
    std::cout << glGetString(GL_VERSION) << std::endl;

    input_system.initialize();
    glfwSetInputMode(window.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    // std::shared_ptr<D3EGraphics::Mesh> mesh = std::make_shared<D3EGraphics::Mesh>(
    // D3EGraphics::VertexLayoutDesc({
    // {D3E_FLOAT3, false},
    // {D3E_FLOAT3, false},
    // {D3E_FLOAT3, false}}),
    // cube_vertex_values,
    // cube_indices_values);

    // mesh->setup();

    std::shared_ptr<D3EGraphics::Shader> shader =
        std::make_shared<D3EGraphics::Shader>("Assets/Shaders/Basic/Basic.vert", "Assets/Shaders/Basic/Basic.frag");

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        800.0f / 600.0f,
        0.1f,
        100.0f
    );

    D3E_CREATE_VB(vb, float, cube_vertex_values);
    D3E_CREATE_EB(eb, cube_indices_values);
    D3E::FinalVertexArray va(
        {{D3E_FLOAT3, false},
         {D3E_FLOAT3, false},
         {D3E_FLOAT3, false}}
    );
    va.PushBuffer(std::move(vb));
    va.PushBuffer(std::move(eb));
    va.finalize();

    glm::mat4 model(1.f);
    // D3E::RenderVertexArray rc(mesh, shader);
    D3E::RenderVertexArray rc(va, shader);
    model = glm::translate(model, glm::vec3(1.f, 0.f, 1.f));

    float rotationSpeed = glm::radians(45.0f); // 45 degrees per second
    float previousTime = glfwGetTime();
    while (!glfwWindowShouldClose(window.get_window()))
    {
        glClearColor(.1f, .1f, .1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentTime = glfwGetTime();
        float  deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        glfwPollEvents();
        input_system.loop(&camera, deltaTime);

        model = glm::rotate(model, rotationSpeed * deltaTime, glm::vec3(0.f, 1.f, 0.f));

        renderer.set_camera_matrices(camera.view_matrix(), projection);
        renderer.submit(std::make_shared<D3E::RenderVertexArray>(rc), model);
        renderer.flush();

        if (glfwGetKey(window.get_window(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window.get_window(), GLFW_TRUE);

        glfwSwapBuffers(window.get_window());
        input_system.clear();
    }
    return 0;
}

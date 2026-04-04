set_project("3DE")
set_version("0.1.0")
set_languages("c++23")

set_targetdir("Executable")
set_objectdir("Binaries/Objects")

local GLFW_DIR  = "ThirdParty/GLFW"
local GLAD_DIR  = "ThirdParty/glad"
local IMGUI_DIR = "ThirdParty/imgui"
local GLM_DIR   = "ThirdParty/glm"
local STB_DIR   = "ThirdParty/stb"
local KHR_DIR   = "ThirdParty/glad/KHR"

target("3DE")
set_kind("binary")
set_rundir("$(projectdir)")

add_files("Sources/Source.cpp")
add_files("Sources/Core/Window/*.cpp")
add_files("Sources/Core/InputSystem/*.cpp")
add_files("Sources/Core/Camera/Camera.cpp")
add_files("Sources/Core/Renderer/RenderCommand.cpp")
add_files("Sources/Core/Renderer/Renderer.cpp")
-- add_files("Sources/Core/Renderer/Renderer.cpp")
add_files("Sources/Graphics/Mesh/VAO/*.cpp")
add_files("Sources/Graphics/Mesh/EBO/*.cpp")
add_files("Sources/Graphics/Mesh/VBO/*.cpp")
add_files("Sources/Graphics/Mesh/Mesh.cpp")
add_files("Sources/Graphics/Node/Node.cpp")
-- add_files("Sources/Graphics/Model/Model.cpp")
add_files("Sources/Graphics/Shader/*.cpp")

add_files(IMGUI_DIR .. "/**.cpp")
add_files(GLM_DIR .. "/**.cpp")
add_files(GLAD_DIR .. "/src/glad.c")

add_includedirs("Sources")
add_includedirs("ThirdParty") -- fixes "glad/glad.h"
add_includedirs(GLFW_DIR)
add_includedirs(IMGUI_DIR)
add_includedirs(IMGUI_DIR .. "/backends")
add_includedirs(GLM_DIR)
add_includedirs(STB_DIR)
add_includedirs(KHR_DIR)

add_linkdirs(GLFW_DIR .. "/lib")
add_links("glfw3")

add_syslinks("opengl32", "gdi32", "user32", "shell32")

target_end()

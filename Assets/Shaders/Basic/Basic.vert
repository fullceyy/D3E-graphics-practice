#version 330 core

layout(location = 0) in vec3 aPos; // Changed to vec3
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;

uniform mat4 model;
uniform mat4 view; // Add view matrix
uniform mat4 projection;

out vec3 vColor;
out vec3 vNormal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vColor = aColor;
    vNormal = mat3(transpose(inverse(model))) * aNormal;
}

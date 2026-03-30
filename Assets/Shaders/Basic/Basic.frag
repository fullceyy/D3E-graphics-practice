#version 330 core

in vec3 vColor; // interpolated color from vertex shader
in vec3 vNormal; // normals available if needed
out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0); // just use vertex color
}

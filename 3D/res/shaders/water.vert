#version 330 core
layout (location = 0) in vec3 vertex; 
layout (location = 1) in vec2 TexCoords;

out vec4 vertexColor;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 color;

void main() {
    //gl_Position = projection * view * model * vec4(vertex, 1.0);
    gl_Position = vec4(vertex, 1.0);
    vertexColor = vec4(color, 1.0);
    texCoords = TexCoords;
}
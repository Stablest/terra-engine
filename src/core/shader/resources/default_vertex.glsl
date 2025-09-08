#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 texUV;

out vec2 TexCoordinates;

uniform mat4 projection;
uniform mat4 model;

void main() {
    TexCoordinates = texUV;
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
}
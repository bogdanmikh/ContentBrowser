#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 transform;

out vec2 v_TexCoordOut;

void main() {
    v_TexCoordOut = aTexCoord;
    gl_Position = vec4(aPos, 1.0) * transform;
}
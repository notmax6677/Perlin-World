#version 330 core

layout (location = 0) in vec3 aPos;

// offset position
uniform vec2 offset;

// scale down to 1%
mat4 scale = mat4(
    0.005f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.005f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.005f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

// translate to new origin
mat4 origin_translate = mat4(
    1.0f, 0.0f, 0.0f, -0.8f + 0.005f, // offset back to proper position by half of width (0.005)
    0.0f, 1.0f, 0.0f, 0.8f - 0.005f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

// translate by offset
mat4 offset_translate = mat4(
    1.0f, 0.0f, 0.0f, offset.x * 0.01f, // offset * width(0.01)
    0.0f, 1.0f, 0.0f, -(offset.y * 0.01f),
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

void main()
{
    gl_Position = scale * vec4(aPos.x, aPos.y, aPos.z, 1.0) * (origin_translate * offset_translate);
}
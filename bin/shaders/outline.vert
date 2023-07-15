#version 330 core

layout (location = 0) in vec3 aPos;

// export clip space position to frag shader
out vec3 position;

// scale down to 80%
mat4 scale = mat4(
    0.8f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.8f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
);

void main()
{
    gl_Position = scale * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    position = (aPos+1)/2; // send normalized 0-1 coords to frag
}
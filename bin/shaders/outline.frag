#version 330 core

out vec4 FragColor;

in vec3 position;

void main() {
    // if pixel within 0.016 (0.01 of screen) borders of square
    if(position.x < 0.008 || position.x > 0.992
        || position.y < 0.008 || position.y > 0.992)
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // red
    else
        FragColor = vec4(0, 0, 0, 0); // transparent
}
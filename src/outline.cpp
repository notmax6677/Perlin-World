#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>

#include "headers/shader.hpp"

using namespace glm;

using namespace std;

// ---

// vertex array object that we will load the index to later
static unsigned int VAO = 0;

// shader object
Shader outlineShader;

void LoadOutline() {
    // vertices array
    float vertices[] = {
        -1.0f, 1.0f, 0.0f, // top left
        1.0f, 1.0f, 0.0f, // top right
        -1.0f, -1.0f, 0.0f, // bottom left
        1.0f, -1.0f, 0.0f, // bottom right
    };

    // indices array
    int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    // vertex buffer object and element buffer object
    unsigned int vbo;
    unsigned int ebo;

    // vertex array object
    unsigned int vao;

    // bind vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // generate and bind vbo
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // load data into vbo
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // generate and bind ebo
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // load data into ebo
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // enables the vertex attribute at 0

    // unbind vao
    glBindVertexArray(0);

    // set VAO to the vao we just made
    VAO = vao;

    // create shader for outline
    outlineShader = Shader("./shaders/outline.vert", "./shaders/outline.frag");
}

void DrawOutline() {
    // bind vao and shader
    glBindVertexArray(VAO);
    outlineShader.Use();

    // draw outline
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // unbind vao and shader
    glUseProgram(0);
    glBindVertexArray(0);
}
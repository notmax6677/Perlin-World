#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <PerlinNoise.hpp>

#include <iostream>

#include "headers/shader.hpp"
#include "headers/square.hpp"
#include "headers/outline.hpp"

#include "headers/settings.hpp"

using namespace glm;

using namespace std;

// screen size
const int INIT_SCR_WIDTH = 800;
const int INIT_SCR_HEIGHT = 800;

// perlin noise
siv::PerlinNoise perlin;

// called when window is resized
void resizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// called when key interaction happens
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // if space key pressed
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // create perlin noise seed
        const siv::PerlinNoise::seed_type seed = rand();

        // create perlin noise with seed
        perlin = siv::PerlinNoise{seed};
    }
}

int main() {
    // string for errors
    const char* errorDescription;

    // initiate glfw and throw error if fails
    if(glfwInit() == GLFW_FALSE) {
        glfwGetError(&errorDescription);
        cout << "ERROR: Failed to initiate GLFW - " << errorDescription << endl;
        return -1;
    }

    // 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // apple
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // window
    GLFWwindow* window = glfwCreateWindow(INIT_SCR_WIDTH, INIT_SCR_HEIGHT, "Perlin World OpenGL", NULL, NULL);

    // if window wasn't generated
    if(window == NULL) {
        // load error into errorDescription
        glfwGetError(&errorDescription);
        // write error and return -1
        cout << "ERROR: Failed to create GLFW window - " << errorDescription << endl;
        return -1;
    }

    // set current gl context
    glfwMakeContextCurrent(window);

    // load glad and throw error if something goes wrong
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "ERROR: Failed to load GLAD." << endl;
        return -1;
    }

    // set initial viewport
    glViewport(0, 0, INIT_SCR_WIDTH, INIT_SCR_HEIGHT);

    // set resize callback
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    // set key callback
    glfwSetKeyCallback(window, keyCallback);

    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // load outline
    LoadOutline();

    // load square
    LoadSquare();

    // set random seed based on system time
    srand(time(nullptr));

    // create perlin noise seed
    const siv::PerlinNoise::seed_type seed = rand();

    // create perlin noise with seed
    perlin = siv::PerlinNoise{seed};

    // loop
    while(!glfwWindowShouldClose(window)) {
        // set clear color buffer
        glClearColor(0.95, 0.95, 0.95, 1);

        // clear with color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // iterate thru x
        for(int x = 0; x < 160; x++) {
            // iterate thru y within every x
            for(int y = 0; y < 160; y++) {
                // get noise at that pos (multiply by 0.1 to basically zoom in)
                double noise = perlin.octave2D_01(x * 0.08, y * 0.08, 4);

                // draw different color square based on noise value
                if(noise < WaterLevel)
                    DrawSquare(vec2(x, y), vec3(0, 0, 1-noise));
                else if(noise > MountLevel)
                    DrawSquare(vec2(x, y), vec3(noise-0.3, noise-0.3, noise-0.3));
                else
                    DrawSquare(vec2(x, y), vec3(0, 1-noise, 0));
            }
        }

        // draw outline
        DrawOutline();

        // swap buffers
        glfwSwapBuffers(window);

        // poll for events
        glfwPollEvents();
    }

    // return 0
    return 0;
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <iostream>

// include the actual header so we can create out-of-class defs for the stuff inside
#include "headers/shader.hpp"

using namespace std;

// function that returns text inside a file at a given path
string loadFile(const char* path) {
    // count the amount of lines read
    int count = 0;

    // write each line to this string
    string text;

    // ifstream class (i think)
    ifstream fileIn(path);

    // if the file is successfully open
    if(fileIn.is_open()) {
        // do while filestream hasn't reached its end
        do {
            // temporary line string
            string line;

            // get current line of filestream and write it into the line string
            getline(fileIn, line);

            // if reading the first line
            if(count == 0)
                text += line;
            // otherwise if not reading the first line and not the last line ("")
            else if(line != "")
                text += "\n" + line; // add a newline before appending line to text so that it's not all on one line

            // if so far nothing has failed or hasn't reached the end
            if(!fileIn.fail())
                count++; // increment count

        } while(!fileIn.fail());

        // close filestream after use
        fileIn.close();
    }
    else {
        cout << "ERROR - FILE AT `" << path << "` COULD NOT BE SUCCESSFULLY OPENED!" << endl;
        return NULL;
    }

    // if got this far, return text
    return text;
}

// out of class definitions

Shader::Shader() {
    ID = 0; // null id
}

// normal constructor
Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // success
    int success;

    // info log
    char infoLog[512];

    // load vertex and fragment shader source as strings
    string vertexSourceStr = loadFile(vertexPath);
    string fragmentSourceStr = loadFile(fragmentPath);

    // get verteex and fragment shader source as c strings (char*)
    const char* vertexSource = vertexSourceStr.c_str();
    const char* fragmentSource = fragmentSourceStr.c_str();

    // create vertex and fragment shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // load vertex shader source
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    // compile vertex shader
    glCompileShader(vertexShader);
    // now check for errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        // load info log for vertex shader
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        // show error message
        cout << "ERROR - VERTEX SHADER COMPILATION FAILED: " << infoLog << endl;
    }

    // now the same process but with fragment shader

    // load fragment shader source
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // compile fragment shader
    glCompileShader(fragmentShader);
    // now check for errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        // load info log for fragment shader
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        // show error message
        cout << "ERROR - FRAGMENT SHADER COMPILATION FAILED: " << infoLog << endl;
    }

    // create the shader program
    unsigned int program = glCreateProgram();

    // attach shaders to program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    // link the attached shaders together to program
    glLinkProgram(program);

    // check for linking errors
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        // load error into infolog
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        // print error
        cout << "ERROR - SHADER PROGRAM LINKING FAILED: " << infoLog << endl;
    }

    // cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set id to program
    ID = program;
}

// use shader function
void Shader::Use() {
    glUseProgram(ID);
}

// uniform setters
void Shader::SetUniform1f(const char* name, float value) {
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::SetUniform2f(const char* name, float value1, float value2) {
    glUniform2f(glGetUniformLocation(ID, name), value1, value2);
}
void Shader::SetUniform3f(const char* name, float value1, float value2, float value3) {
    glUniform3f(glGetUniformLocation(ID, name), value1, value2, value3);
}
void Shader::SetUniform4f(const char* name, float value1, float value2, float value3, float value4) {
    glUniform4f(glGetUniformLocation(ID, name), value1, value2, value3, value4);
}
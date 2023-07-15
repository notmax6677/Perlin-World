#ifndef _SHADERS_HPP_
#define _SHADERS_HPP_

class Shader {
    // public values
    public:
        // default constructor
        Shader();

        // constructor
        Shader(const char* vertexPath, const char* fragmentPath);

        // shader program ID
        unsigned int ID;

        // use the shadder program
        void Use();

        // set 1 uniform float value
        void SetUniform1f(const char* name, float value);

        // set 2 uniform float values
        void SetUniform2f(const char* name, float value1, float value2);

        // set 3 uniform float values
        void SetUniform3f(const char* name, float value1, float value2, float value3);

        // set 4 uniform float values
        void SetUniform4f(const char* name, float value1, float value2, float value3, float value4);
};

#endif
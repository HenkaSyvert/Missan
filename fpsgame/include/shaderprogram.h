#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <glm/glm.hpp>

namespace missan {

    class ShaderProgram {

    private:
        unsigned int programID, vertexShader, fragmentShader;

        void PrintGLErrorMsg(unsigned int id);

        unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSource);

        GLint GetUniformLocation(std::string name);

    public:
        ShaderProgram(std::string vertexFile, std::string fragmentFile);

        ~ShaderProgram();

        void Use();

        void Stop();

        void SetUniform4f(std::string name, glm::vec4& v);
        void SetUniform3f(std::string name, glm::vec3& v);
        void SetUniformMat4(std::string name, glm::mat4& m);
        void SetUniform1i(std::string name, int val);
    };

}
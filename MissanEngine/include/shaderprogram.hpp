#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>


namespace missan {

    class ShaderProgram {

    private:
        GLuint programID; 

        void PrintGLErrorMsg(GLuint id);
        GLuint CompileShader(GLuint shaderType, const std::string& shaderCode);
        GLint GetUniformLocation(const std::string& name) const;

    public:
        ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
        void Use();

        // Uniform access
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetBool(const std::string& name, bool value) const;

        void SetVec3(const std::string& name, glm::vec3& value) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
       
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetVec4(const std::string& name, float x, float y, float z, float w) const;

        void SetMat2(const std::string& name, const glm::mat2& value) const;
        void SetMat3(const std::string& name, const glm::mat3& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;
        
    };

}
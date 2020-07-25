#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>


namespace missan {

    class ShaderProgram {

    private:
        GLuint programID; 

        GLint GetUniformLocation(const std::string& uniformVariableName) const;

    public:
        ShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
        void Use() const;

        // Uniform variable setter functions
        void SetInt  (const std::string& uniformVariableName, int   value) const;
        void SetFloat(const std::string& uniformVariableName, float value) const;
        void SetBool (const std::string& uniformVariableName, bool  value) const;

        void SetVec3(const std::string& uniformVariableName, const glm::vec3& value) const;
        void SetVec3(const std::string& uniformVariableName, float x, float y, float z) const;
       
        void SetVec4(const std::string& uniformVariableName, const glm::vec4& value) const;
        void SetVec4(const std::string& uniformVariableName, float x, float y, float z, float w) const;

        void SetMat2(const std::string& uniformVariableName, const glm::mat2& value) const;
        void SetMat3(const std::string& uniformVariableName, const glm::mat3& value) const;
        void SetMat4(const std::string& uniformVariableName, const glm::mat4& value) const;
        
    };

}
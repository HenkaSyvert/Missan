#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace Missan {

    /// 
    /// Program that runs on the GPU
    class ShaderProgram {

    public:

        GLuint programId;

        /// 
        /// Compiles new Shader from source code
        ShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
     


        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetInt  (const std::string& uniformVariableName, int   value) const;
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetFloat(const std::string& uniformVariableName, float value) const;
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetBool (const std::string& uniformVariableName, bool  value) const;
        
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetVec3(const std::string& uniformVariableName, const glm::vec3& value) const;
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetVec3(const std::string& uniformVariableName, float x, float y, float z) const;
        
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetVec4(const std::string& uniformVariableName, const glm::vec4& value) const;
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetVec4(const std::string& uniformVariableName, float x, float y, float z, float w) const;
        
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetMat2(const std::string& uniformVariableName, const glm::mat2& value) const;
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetMat3(const std::string& uniformVariableName, const glm::mat3& value) const;
        /// 
        /// Sets uniform variable of ShaderProgram (i.e. on the GPU) to value
        void SetMat4(const std::string& uniformVariableName, const glm::mat4& value) const;
        
    private:
        

        GLint GetUniformLocation(const std::string& uniformVariableName) const;

    };

}
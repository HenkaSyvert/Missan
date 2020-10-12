#pragma once

#include "missanpch.hpp"


namespace Missan {

    /// 
    /// Program that runs on the GPU
    class ShaderProgram {

    public:

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
        


        /// NOT PART OF PUBLIC API ////////////////////////////////////////
        void Use() const;

    private:
        GLuint programID;

        GLint GetUniformLocation(const std::string& uniformVariableName) const;

    };

}
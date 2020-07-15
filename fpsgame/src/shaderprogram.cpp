#include "shaderprogram.hpp"

#include <vector>
#include <iostream>

#include "loader.hpp"

using namespace missan;

// PRIVATE
void ShaderProgram::PrintGLErrorMsg(GLuint id) {
	int maxLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

	std::vector<char> infoLog(maxLength);
	glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

	std::cout << std::string(infoLog.data()) << std::endl;
}

GLuint ShaderProgram::CompileShader(GLuint shaderType, const std::string& shaderCode) {
	GLuint shader = glCreateShader(shaderType);
	const char* source = shaderCode.c_str();
	glShaderSource(shader, 1, &source, nullptr);

	glCompileShader(shader);
	int isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, (int*)&isCompiled);
	if (isCompiled == GL_FALSE) {

		PrintGLErrorMsg(shader);
		glDeleteShader(shader);
		exit(EXIT_FAILURE);
	}

	return shader;
}

GLint ShaderProgram::GetUniformLocation(const std::string& name) const{
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location == -1) std::cout << "couldn't find uniform \"" << name << "\"\n";
	return location;
}



// PUBLIC
ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
	programID = glCreateProgram();
	GLuint vertexShader, fragmentShader;
	
	std::string vertexCode = Loader::LoadShader(vertexPath);
	vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode);
	glAttachShader(programID, vertexShader);

	std::string fragmentCode = Loader::LoadShader(fragmentPath);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);
	glAttachShader(programID, fragmentShader);

	glLinkProgram(programID);
	int isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		PrintGLErrorMsg(programID);
		glDeleteProgram(programID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	glDetachShader(programID, vertexShader);
	glDeleteShader(vertexShader);

	glDeleteShader(fragmentShader);
	glDetachShader(programID, fragmentShader);

}

void ShaderProgram::Use() {
	glUseProgram(programID);
}




// UNIFORM ACCESS
void ShaderProgram::SetInt(const std::string& name, int value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniform1i(location, value);
}

void ShaderProgram::SetFloat(const std::string& name, float value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniform1f(location, value);
}

void ShaderProgram::SetBool(const std::string& name, bool value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniform1i(location, (int)value);
}



void ShaderProgram::SetVec3(const std::string& name, glm::vec3& value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniform3fv(location, 1, &value[0]);
}

void ShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniform3f(location, x, y, z);
}

void ShaderProgram::SetVec4(const std::string& name, const glm::vec4& value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniform4fv(location, 1, &value[0]);
}

void ShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniform4f(location, x, y, z, w);
}



void ShaderProgram::SetMat2(const std::string& name, const glm::mat2& value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetMat3(const std::string& name, const glm::mat3& value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetMat4(const std::string& name, const glm::mat4& value) const {
	auto location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}


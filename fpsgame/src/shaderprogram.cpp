#include "shaderprogram.h"

#include <vector>
#include <iostream>

#include "loader.h"

using namespace missan;

// PRIVATE
void ShaderProgram::PrintGLErrorMsg(unsigned int id) {
	int maxLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

	std::vector<char> infoLog(maxLength);
	glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

	std::cout << std::string(infoLog.data()) << std::endl;
}

unsigned int ShaderProgram::CompileShader(unsigned int shaderType, const std::string& shaderSource) {
	unsigned int shader = glCreateShader(shaderType);
	const char* source = shaderSource.c_str();
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

GLint ShaderProgram::GetUniformLocation(std::string name){
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location == -1) std::cout << "couldn't find uniform \"" << name << "\"\n";
	return location;
}

// PUBLIC
ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile) {
	std::string vssrc = Loader::LoadShader(vertexFile);
	std::string fssrc = Loader::LoadShader(fragmentFile);

	vertexShader = CompileShader(GL_VERTEX_SHADER, vssrc);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fssrc);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
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

	//glDetachShader(programID, vertexShader);
	//glDetachShader(programID, fragmentShader);
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(programID);
	glDetachShader(programID, vertexShader);
	glDetachShader(programID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::Use() {
	glUseProgram(programID);
}

void ShaderProgram::Stop() {
	glUseProgram(0);
}

void ShaderProgram::SetUniform4f(std::string name, glm::vec4& v) {
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform4fv(location, 1, &v[0]);
}

void ShaderProgram::SetUniform3f(std::string name, glm::vec3& v) {
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform3fv(location, 1, &v[0]);
}

void ShaderProgram::SetUniformMat4(std::string name, glm::mat4& m) {
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void ShaderProgram::SetUniform1i(std::string name, int val) {
	GLint location = GetUniformLocation(name);
	if (location != -1) glUniform1i(location, val);
}


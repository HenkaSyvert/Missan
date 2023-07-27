#include "pch.hpp"
#include "shader.hpp"
#include <spdlog/spdlog.h>

using namespace Missan;
using namespace std;
using namespace glm;

Shader* Shader::unlit = nullptr;
Shader* Shader::phong = nullptr;

string LoadShader(const string& fileName) {
	fstream input(fileName);

	if (!input.is_open()) {
		spdlog::error("cannot open {}", fileName);
		exit(EXIT_FAILURE);
	}

	string str;
	while (input.peek() != EOF)
		str += input.get();

	return str;
}

void PrintCompilationError(GLuint shader) {
	int length;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

	GLchar* infoLog = (GLchar*)alloca(length);
	glGetShaderInfoLog(shader, length, NULL, infoLog);

	spdlog::error(infoLog);
}

GLuint CompileShader(GLuint shaderType, const string& shaderSourceCode) {
	GLuint shader = glCreateShader(shaderType);
	const char* source = shaderSourceCode.c_str();
	glShaderSource(shader, 1, &source, nullptr);

	glCompileShader(shader);
	int isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, (int*)&isCompiled);
	if (isCompiled == GL_FALSE) {

		PrintCompilationError(shader);
		glDeleteShader(shader);
		exit(EXIT_FAILURE);
	}

	return shader;
}

GLint Shader::GetUniformLocation(const string& uniformVariableName) const{
	GLint location = glGetUniformLocation(programId, uniformVariableName.c_str());
	if (location == -1)
		cout << "shader error: could not find uniform variable \"" << uniformVariableName << "\"\n";
	return location;
}



Shader::Shader(const string& path) {
	programId = glCreateProgram();
	GLuint vertexShader, fragmentShader;
	
	string vertexSourceCode = "#version 330 core\n#define COMPILE_VERTEX\n" + LoadShader(path);
	vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSourceCode);
	glAttachShader(programId, vertexShader);

	string fragmentSourceCode = "#version 330 core\n#define COMPILE_FRAGMENT\n" + LoadShader(path);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSourceCode);
	glAttachShader(programId, fragmentShader);

	glLinkProgram(programId);
	int isLinked = 0;
	glGetProgramiv(programId, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE) {
		PrintCompilationError(programId);
		glDeleteProgram(programId);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	glDetachShader(programId, vertexShader);
	glDeleteShader(vertexShader);

	glDeleteShader(fragmentShader);
	glDetachShader(programId, fragmentShader);

}


// UNIFORM VARIABLE SETTER FUNCTIONS
void Shader::SetInt(const string& uniformVariableName, int value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform1i(location, value);
}

void Shader::SetFloat(const string& uniformVariableName, float value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform1f(location, value);
}

void Shader::SetBool(const string& uniformVariableName, bool value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform1i(location, (int)value);
}



void Shader::SetVec3(const string& uniformVariableName, const vec3& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform3fv(location, 1, &value[0]);
}

void Shader::SetVec3(const string& uniformVariableName, float x, float y, float z) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform3f(location, x, y, z);
}


void Shader::SetVec4(const string& uniformVariableName, const vec4& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform4fv(location, 1, &value[0]);
}

void Shader::SetVec4(const string& uniformVariableName, float x, float y, float z, float w) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform4f(location, x, y, z, w);
}


void Shader::SetMat2(const string& uniformVariableName, const mat2& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat3(const string& uniformVariableName, const mat3& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(const string& uniformVariableName, const mat4& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}


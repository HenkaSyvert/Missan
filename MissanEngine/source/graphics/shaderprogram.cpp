#include "graphics/shaderprogram.hpp"

using namespace missan;

// PRIVATE
std::string LoadShader(const std::string& filename) {

	std::string shaderDirectory = "resources/shaders/";

	std::string filePath = shaderDirectory + filename;
	std::fstream input(filePath);

	if (!input.is_open()) {
		std::cout << "error: could not open \"" << filePath << "\"\n";
		exit(EXIT_FAILURE);
	}

	std::string str;
	while (input.peek() != EOF)
		str += input.get();

	return str;
}

void PrintGLErrorMsg(GLuint id) {
	int maxLength;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

	std::vector<char> infoLog(maxLength);
	glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

	std::cout << std::string(infoLog.data()) << std::endl;
}

GLuint CompileShader(GLuint shaderType, const std::string& shaderSourceCode) {
	GLuint shader = glCreateShader(shaderType);
	const char* source = shaderSourceCode.c_str();
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

GLint ShaderProgram::GetUniformLocation(const std::string& uniformVariableName) const{
	GLint location = glGetUniformLocation(programID, uniformVariableName.c_str());
	if (location == -1) std::cout << "shader error: could not find uniform variable \"" << uniformVariableName << "\"\n";
	return location;
}



// PUBLIC
ShaderProgram::ShaderProgram(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	programID = glCreateProgram();
	GLuint vertexShader, fragmentShader;
	
	std::string vertexSourceCode = LoadShader(vertexShaderFilePath);
	vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSourceCode);
	glAttachShader(programID, vertexShader);

	std::string fragmentSourceCode = LoadShader(fragmentShaderFilePath);
	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSourceCode);
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

void ShaderProgram::Use() const {
	glUseProgram(programID);
}




// UNIFORM VARIABLE SETTER FUNCTIONS
void ShaderProgram::SetInt(const std::string& uniformVariableName, int value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform1i(location, value);
}

void ShaderProgram::SetFloat(const std::string& uniformVariableName, float value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform1f(location, value);
}

void ShaderProgram::SetBool(const std::string& uniformVariableName, bool value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform1i(location, (int)value);
}



void ShaderProgram::SetVec3(const std::string& uniformVariableName, const glm::vec3& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform3fv(location, 1, &value[0]);
}

void ShaderProgram::SetVec3(const std::string& uniformVariableName, float x, float y, float z) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform3f(location, x, y, z);
}



void ShaderProgram::SetVec4(const std::string& uniformVariableName, const glm::vec4& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform4fv(location, 1, &value[0]);
}

void ShaderProgram::SetVec4(const std::string& uniformVariableName, float x, float y, float z, float w) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniform4f(location, x, y, z, w);
}



void ShaderProgram::SetMat2(const std::string& uniformVariableName, const glm::mat2& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetMat3(const std::string& uniformVariableName, const glm::mat3& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetMat4(const std::string& uniformVariableName, const glm::mat4& value) const {
	auto location = GetUniformLocation(uniformVariableName);
	if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}


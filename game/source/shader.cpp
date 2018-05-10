#include"../include/shader.h"

#include"../include/config.h"

#define GLEW_STATIC
#include<gl\glew.h>

#include<fstream>
#include<iostream>
#include<vector>

Shader* Shader::s_Shader = nullptr;

void Shader::init()
{
	s_Shader = new Shader("assets\\vertex_shader.txt", "assets\\fragment_shader.txt");
	s_Shader->bind();
	s_Shader->setUniformMat4f(Matrix4x4::Orthographic(0, WIDTH, HEIGHT, 0, -1, 1), "projection_matrix");
}

Shader & Shader::getShader()
{
	return *s_Shader;
}

Shader::Shader(std::string a_vertexPath, std::string a_fragmentPath)
{
	// Assume glew and everything is already initiated 
	// Compile and create shader program with the parameter arguments

	std::string vertexSource;
	std::string fragmentSource;

	std::ifstream fileStream(a_vertexPath);
	std::string line;
	// Vertex Source to String
	while (std::getline(fileStream, line)) {
		vertexSource += line + "\n";
	}
	fileStream.close();
	line.clear();
	// Fragment Source to String
	fileStream.open(a_fragmentPath);
	while (std::getline(fileStream, line)) {
		fragmentSource += line + "\n";
	}
	fileStream.close();

	// Vertex Shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* temp = vertexSource.c_str();
	glShaderSource(vertexShader, 1, &temp, nullptr);
	glCompileShader(vertexShader);
	didCompile(vertexShader);

	// Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* temp2 = fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &temp2, nullptr);
	glCompileShader(fragmentShader);
	didCompile(fragmentShader);

	// Link the shader program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);

	glDetachShader(m_ID, vertexShader);
	glDetachShader(m_ID, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Done!
}

Shader::~Shader()
{
	if (glIsProgram(m_ID)) {
		glDeleteProgram(m_ID);
	}
}

void Shader::bind()
{
	glUseProgram(m_ID);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setUniform1i(const int a_value, std::string a_name)
{
	glUniform1i(getUniformLocation(a_name), a_value);
}

void Shader::setUniformMat4f(const Matrix4x4 & a_matrix, std::string a_name)
{
	glUniformMatrix4fv(getUniformLocation(a_name), 1, false, a_matrix.elements);
}

void Shader::setUniform4f(const Vector4 & a_vector, std::string a_name)
{
	glUniform4f(getUniformLocation(a_name), a_vector.x, a_vector.y, a_vector.z, a_vector.a);
}

void Shader::setUniform2f(const Vector2 & a_vector, std::string a_name)
{
	glUniform2f(getUniformLocation(a_name), a_vector.x, a_vector.y);
}

bool Shader::didCompile(int a_shader)
{
	int result = 0;
	glGetShaderiv(a_shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(a_shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(a_shader, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		for (GLchar c : errorLog) {
			std::cout << c;
		}

		// Exit with failure.
		glDeleteShader(a_shader); // Don't leak the shader.
		return false;
	}
	return true;
}

int Shader::getUniformLocation(std::string a_name)
{
	return glGetUniformLocation(m_ID, a_name.c_str());
}

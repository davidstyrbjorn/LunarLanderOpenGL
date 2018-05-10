#pragma once

#include<string>

#include"../include/matrix4x4.h"
#include"../include/vector.h"

class Shader {

private:
	int m_ID;
	// Static Shader objects
	static Shader* s_Shader;

	bool didCompile(int a_shader);
	int getUniformLocation(std::string a_name);

public:
	static void init();
	static Shader& getShader();

public:
	Shader(std::string a_vertexPath, std::string a_fragmentPath);
	~Shader();

	void bind();
	void unbind();

	void setUniform1i(const int a_value, std::string a_name);
	void setUniformMat4f(const Matrix4x4& a_matrix, std::string a_name);
	void setUniform4f(const Vector4& a_vector, std::string a_name);
	void setUniform2f(const Vector2& a_vector, std::string a_name);

};
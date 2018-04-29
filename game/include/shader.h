#pragma once

#include<string>

#include"../include/matrix4x4.h"
#include"../include/vector.h"

class Shader {

private:
	int m_ID;
	// Static Shader objects
	static Shader s_VertexShader;
	static Shader s_FragmentShader;

	bool didCompile(int a_shader);
	int getUniformLocation(std::string a_name);

public:
	Shader(std::string a_vertexPath, std::string a_fragmentPath);
	~Shader();

	void bind();
	void unbind();

	void setUniformMat4f(const Matrix4x4& a_matrix, std::string a_name);
	void setUniform4f(const Vector4& a_vector, std::string a_name);
	void setUniform2f(const Vector2& a_vector, std::string a_name);

};
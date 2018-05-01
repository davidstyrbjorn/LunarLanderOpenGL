#include"../include/lander.h"

#include"../include/shader.h"
#include"../include/config.h"

#define GLEW_STATIC
#include<gl\glew.h>

const float Lander::s_Width = 32.5;
const float Lander::s_Height = 40;

Lander::Lander()
{
	Vector4 color(1, 1, 1, 1);
	float y = s_Height;
	float x = s_Width;

	Vertex landerVerts[] = {
		{ Vector2(0,0),							color }, // 0
		{ Vector2(-x / 2, y / 3),				color }, // 1
		{ Vector2(-x / 3.0f, (3 * y) / 5),		color }, // 2
		{ Vector2(+x / 3.0f, (3 * y) / 5),		color }, // 3
		{ Vector2(+x / 2, y / 3),				color }, // 4
		{ Vector2(-x / 2, y),					color }, // 5
		{ Vector2(x / 2, y),					color } // 6
	};

	unsigned int indexes[] = {
		1, 0, 4,
		1, 4, 2,
		2, 4, 3,
		2, 3, 5,
		5, 3, 6
	};

	unsigned int indexCount = 3 * 5;

	// Create the OpenGL buffer objects for the lander
	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(landerVerts), landerVerts, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	// Setup vertex array
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector2)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Lander::~Lander()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void Lander::draw()
{
	// OpenGL draw routine
	// Shader Uniform
	Shader::getShader().setUniformMat4f(Matrix4x4::Translation(Vector3(m_Pos.x, m_Pos.y, 0)), "model_matrix");

	// Bind
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	// Draw Call
	glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, nullptr);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
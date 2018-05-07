#include"../include/lander.h"

#include"../include/shader.h"
#include"../include/config.h"

#define GLEW_STATIC
#include<gl\glew.h>

#include<iostream>

const float Lander::s_Width = 32.5;
const float Lander::s_Height = 40;

Lander::Lander() : m_PhysicsBody()
{
	Vector4 color(1, 1, 1, 1);
	float y = s_Height;
	float x = s_Width;

	m_LanderVerticesMain.push_back({ Vector2(x / 2, 0), color });
	m_LanderVerticesMain.push_back({ Vector2(0, y*0.7f), color });
	m_LanderVerticesMain.push_back({ Vector2(x, y*0.7f), color });
	m_LanderVerticesMain.push_back({ Vector2(x / 2, 0), color });

	m_LanderVerticesLower.push_back({ Vector2(0, y), color });
	m_LanderVerticesLower.push_back({ Vector2(x*0.2f, y*0.7f), color });
	m_LanderVerticesLower.push_back({ Vector2(x*0.8f, y*0.7f), color });
	m_LanderVerticesLower.push_back({ Vector2(x, y), color });

	// Create the OpenGL buffer objects for the lander
	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Setup vertex array
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector2)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	Shader::getShader().setUniformMat4f(Matrix4x4::Translation(Vector3(m_PhysicsBody.getPosition().x, m_PhysicsBody.getPosition().y, 0)), "model_matrix");

	// Bind
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Drawing main part of lander
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_LanderVerticesMain.size(), m_LanderVerticesMain.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	// Drawing lower part of lander
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_LanderVerticesLower.size(), m_LanderVerticesLower.data(), GL_STATIC_DRAW);
	glDrawArrays(GL_LINE_STRIP, 0, 4);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Lander::update()
{
	m_PhysicsBody.update();
}

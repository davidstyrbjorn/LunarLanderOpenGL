#include"../include/fuel.h"

#define GLEW_STATIC
#include<gl\glew.h>

FuelBar::FuelBar(PhysicsBody & a_LanderBody) : m_LanderBody(a_LanderBody)
{
	// Initalize the primitive
	// type: rectangle
	// size: (150, 40)
	// color: ?

	m_Pos = Vector2(20, 20);
	m_Color = Vector4(0, 0.5f, 1, 1);
	m_Size = Vector2(150, 40);

	Vertex data[] = {
		{ m_Pos, m_Color },
		{ Vector2(m_Pos.x, m_Pos.y + m_Size.y), m_Color },

		{ m_Pos + m_Size, m_Color },
		{ Vector2(m_Pos.x + m_Size.x, m_Pos.y), m_Color }
	};
	GLuint indices[] = { 0, 1, 2,   0, 2, 3 };

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// VBO creation
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);
	// Upload the static part of the primitive
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data), data);

	// VAO attribs
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector2)));

	// IBO creation
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

FuelBar::~FuelBar()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
	glDeleteVertexArrays(1, &m_VAO);
}

void FuelBar::draw()
{
	// Bind
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	float ratio = (float)m_LanderBody.getFuel() / (float)m_LanderBody.getMaxFuel(); // Ratio between 0 and 1 for the width
	// Last two verts
	Vertex data[] = {
		{ m_Pos + Vector2(m_Size.x*ratio, m_Size.y), Vector4(0,1,0,1) },
		{ Vector2(m_Pos.x + m_Size.x*ratio, m_Pos.y), Vector4(0,1,0,1) }
	};
	// Update the last two verts please
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertex) * 2, sizeof(data), data);

	// Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
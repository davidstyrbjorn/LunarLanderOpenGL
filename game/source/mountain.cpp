#include"../include/mountain.h"

#include"../include/mountain_generator.h"

#define GLEW_STATIC
#include<gl\glew.h>

Mountain::Mountain()
{
	// m_VBO
	// m_VAO
	// m_IBO

	m_Points = getLandscape();
	std::vector<Vertex> data;
	for (int x = 0; x < WIDTH; x++) {
		Vertex v;
		v.pos = Vector2(x, m_Points[x]);
		v.color = Vector4(1, 1, 1, 1);
		data.push_back(v);
	}

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), 0); // Position
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector2))); // Color
}
Mountain::~Mountain()
{

}

void Mountain::draw()
{
	// Draw call here
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glDrawArrays(GL_LINES, 0, m_Points.size());

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
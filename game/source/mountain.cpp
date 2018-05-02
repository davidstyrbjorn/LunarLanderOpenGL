#include"../include/mountain.h"

#include"../include/mountain_generator.h"

#define GLEW_STATIC
#include<gl\glew.h>

Mountain::Mountain()
{
	// m_VBO
	// m_VAO
	// m_IBO

	//m_Points = getLandscape();

	std::vector<int> f = getLandscape();
	std::vector<Vertex> data;
	for (int x = 0; x < WIDTH; x++) {
		if (x != 0 && x != WIDTH - 1) {
			// We need to add the previous point + current point
			Vertex prevVertex;
			prevVertex.pos = Vector2(x - 1, f[x - 1]);
			prevVertex.color = Vector4(1, 0, 0, 1);
			data.push_back(prevVertex);

			Vertex newVertex;
			newVertex.pos = Vector2(x, f[x]);
			newVertex.color = Vector4(1, 0, 0, 1);
			data.push_back(newVertex);
		}
		else {
			// Only add current point because we're at the end of the line segment
			Vertex vertex;
			vertex.pos = Vector2(x, f[x]);
			vertex.color = Vector4(1, 0, 0, 1);
			data.push_back(vertex);
		}
	}

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*data.size(), &data[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vertex), 0); // Position
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(Vector2))); // Color

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
Mountain::~Mountain()
{

}

void Mountain::draw()
{
	// Draw call here
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glDrawArrays(GL_LINES, 0, WIDTH*2-2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
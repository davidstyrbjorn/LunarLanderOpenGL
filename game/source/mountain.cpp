#include"../include/mountain.h"

#include"../include/mountain_generator.h"
#include"../include/shader.h"
#include"../include/lander.h"

#define GLEW_STATIC
#include<gl\glew.h>

#include<iostream>
#include<random>
#include<time.h>

Mountain::Mountain()
{
	std::vector<Vertex> data;
	Vector4 color(1, 1, 1, 1);
	Vector4 color2(0, 1, 0, 1);
	m_Points = getLandscape();
	// int randNum = rand()%(max-min + 1) + min; 
	int landingXStart = rand() % (WIDTH + 1);
	std::cout << landingXStart << std::endl;
	int landTempY;
	bool isPlottingLanding = false;

	for (int x = 0; x < m_Points.size(); x++)
	{
		if (x == landingXStart) {
			isPlottingLanding = true;
			landTempY = m_Points[x];
		}

		// CHeck if we're supposed to be plotting the landing thingy
		if (isPlottingLanding) {
			if (x < landingXStart + Lander::s_Width*1.5f) {
				data.push_back({ Vector2(x, HEIGHT - landTempY), color2 });
			}
			else {
				//data.push_back({ Vector2(x, HEIGHT - m_Points[x]), color });
				isPlottingLanding = false;

			}
		}
		if(!isPlottingLanding)
		{
			data.push_back({ Vector2(x, HEIGHT - m_Points[x]), color });
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
	Shader::getShader().setUniformMat4f(Matrix4x4::Translation(Vector3(0, 0, 0)), "model_matrix");

	// Draw call here
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glDrawArrays(GL_LINE_STRIP, 0, m_Points.size()
	);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
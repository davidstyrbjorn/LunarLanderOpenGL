#include"../include/lander.h"

#include"../include/shader.h"
#include"../include/config.h"
#include"../include/mountain.h"
#include"../include/game_master.h"

#define GLEW_STATIC
#include<gl\glew.h>

#include<iostream>

const float Lander::s_Width = 32.5;
const float Lander::s_Height = 40;

Lander::Lander() : m_PhysicsBody(), m_FuelBar(m_PhysicsBody)
{
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

void Lander::lost()
{
	m_Color = Vector4(1, 0, 0, 1);
}

void Lander::reset()
{
	m_PhysicsBody.setPosition(Vector2(0, 0));
	m_PhysicsBody.setFuel(m_PhysicsBody.getFuel() + 50);
}

void Lander::draw()
{
	// OpenGL draw routine

	// Setting the model_matrix is one method of rendering at a specifik position
	//Shader::getShader().setUniformMat4f(Matrix4x4::Translation(Vector3(m_PhysicsBody.getPosition().x, m_PhysicsBody.getPosition().y, 0)), "model_matrix");
	
	// Update the vertices inside the buffer to align accordingy with position
	auto pos = m_PhysicsBody.getPosition();

	m_LanderVerticesMain.clear();
	m_LanderVerticesMain.push_back({ Vector2(s_Width / 2, 0) + pos, m_Color });
	m_LanderVerticesMain.push_back({ Vector2(0, s_Height*0.7f) + pos, m_Color });
	m_LanderVerticesMain.push_back({ Vector2(s_Width, s_Height*0.7f) + pos, m_Color });
	m_LanderVerticesMain.push_back({ Vector2(s_Width / 2, 0) + pos, m_Color });

	m_LanderVerticesLower.clear();
	m_LanderVerticesLower.push_back({ Vector2(0, s_Height) + pos, m_Color });
	m_LanderVerticesLower.push_back({ Vector2(s_Width*0.2f, s_Height*0.7f) + pos, m_Color });
	m_LanderVerticesLower.push_back({ Vector2(s_Width*0.8f, s_Height*0.7f) + pos, m_Color });
	m_LanderVerticesLower.push_back({ Vector2(s_Width, s_Height) + pos, m_Color });
	m_LandingGearPosition[0] = Vector2(0, s_Height) + pos;
	m_LandingGearPosition[1] = Vector2(s_Width, s_Height) + pos;

	// Collision check between landing gear points and the terrain
	// This is a breeze because we have the mountain outlayed as a x-y graph where the landing gear are just two points -> collision is true if the landing gear position is lower than corresponding terrain position
	std::vector<int> m_Mountain = Mountain::instance()->getPoints();
	if (m_LandingGearPosition[0].x >= 0 && m_LandingGearPosition[1].x < WIDTH) {
		if (m_LandingGearPosition[0].y > HEIGHT - m_Mountain.at(m_LandingGearPosition[0].x) ||
			m_LandingGearPosition[1].y > HEIGHT - m_Mountain.at(m_LandingGearPosition[1].x)) {
			// Check if we're within the bounds of the landing area
			if (m_LandingGearPosition[0].x > Mountain::instance()->getLandingPadBounds().x &&
				m_LandingGearPosition[1].x < Mountain::instance()->getLandingPadBounds().y) {
				GameMaster::landingPerformed();
			}
			else {
				GameMaster::crashPerformed();
			}
		}
	}

	m_FuelBar.draw();

	//// Bind
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

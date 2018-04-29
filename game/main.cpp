#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include"include\shader.h"
#include"include\matrix4x4.h"

int main() 
{
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
	}
	GLFWwindow *window = glfwCreateWindow(480, 480, "Lunar Lander", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 480, 480);

	glewInit();
	glewExperimental = true;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Test
	Shader shader("assets\\vertex_shader.txt", "assets\\fragment_shader.txt");
	shader.bind();
	shader.setUniformMat4f(Matrix4x4::Orthographic(0, 480, 480, 0, -1, 1), "projection_matrix");

	// Triangle Vertice
	float vertices[] = {
		0, 0,
		0, 100,
		100, 100
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr); // Position

	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
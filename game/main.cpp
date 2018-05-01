#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include"include\shader.h"
#include"include\matrix4x4.h"
#include"include\lander.h"
#include"include\mountain.h"

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

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Test
	Shader::init(); // Creates the static shader object

	Lander lander;
	lander.setPosition(Vector2(100, 100));

	Mountain mountain;

	while (!glfwWindowShouldClose(window)) 
	{
		glClear(GL_COLOR_BUFFER_BIT);

		lander.draw();
		mountain.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
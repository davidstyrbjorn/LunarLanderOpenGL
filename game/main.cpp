#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include"include\shader.h"
#include"include\matrix4x4.h"
#include"include\lander.h"
#include"include\mountain.h"
#include"include\config.h"
#include"include\clock.h"

int main() 
{
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
	}
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Lunar Lander", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSwapInterval(1);

	glewInit();
	glewExperimental = true;

	// Test
	Shader::init(); // Creates the static shader object

	Lander lander;
	lander.setPosition(Vector2(100, 20));
	Mountain mountain;

	Clock clock;
	clock.Start();
	float deltaTime = 0;
	double k1, k2;

	while (!glfwWindowShouldClose(window)) 
	{
		k1 = clock.GetTicks();
		glClear(GL_COLOR_BUFFER_BIT);

		lander.draw();
		mountain.draw();

		k2 = clock.GetTicks();
		lander.update(k2 - k1);

		glfwSwapBuffers(window);
		glfwPollEvents();

		clock.Reset();
	}

	glfwTerminate();
	return 0;
}
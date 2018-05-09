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
#include"include\input.h"
#include"include\game_master.h"

#define FPS 60
#define MS 1000/FPS

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
	Input::instance(); // Callback creation

	Lander lander;
	lander.setPosition(Vector2(100, 20));
	Mountain* mountain = Mountain::instance();
	mountain->init();

	Clock clock;
	clock.Start();

	while (!glfwWindowShouldClose(window)) 
	{
		if (clock.GetTicks() > MS) 
		{
			glClear(GL_COLOR_BUFFER_BIT);

			lander.draw();
			mountain->draw();

			if (GameMaster::gameWon()) {
				// Render "you just won!"
				if (Input::instance()->isKeyDown(GLFW_KEY_R)) {
					// Reset the game 
					lander.reset();
					mountain->reset();
					GameMaster::reset();
				}
			}
			else if (GameMaster::gameLost()) {
				// Render "you just lost!"
				lander.lost();
				mountain->lost();
			}
			else {
				lander.update();
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}
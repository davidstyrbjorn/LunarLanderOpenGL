#include<iostream>

#define GLEW_STATIC
#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<random>

#include"include\shader.h"
#include"include\matrix4x4.h"
#include"include\lander.h"
#include"include\mountain.h"
#include"include\config.h"
#include"include\clock.h"
#include"include\input.h"
#include"include\game_master.h"
#include"include\sound.h"

#include<al.h>
#include<alc.h>

#define FPS 60
#define MS 1000/FPS

int main() 
{
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
	}
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Lunar Lander", nullptr, nullptr);
	glfwSetWindowTitle(window, "Lunar Lander || SCORE: 0");
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

	bool shakeTrigger = false;
	int shakeTimer = 0;
	int shakeStrength = 20;

	ALCcontext *context;
	ALCdevice *device = alcOpenDevice(NULL); // Defaults to "preferred device"
	if (device != nullptr) {
		context = alcCreateContext(device, NULL);
		alcMakeContextCurrent(context);
	}

	Sound sound("assets\\gas.wav");
	sound.play();

	while (!glfwWindowShouldClose(window)) 
	{
		if (clock.GetTicks() > MS) 
		{
			glClear(GL_COLOR_BUFFER_BIT);

			lander.draw();
			mountain->draw();

			if (Input::instance()->isKeyDown(GLFW_KEY_W)) {
				sound.play();
			}

			if (GameMaster::gameWon()) {
				// Render "you just won!"
				if (Input::instance()->isKeyDown(GLFW_KEY_SPACE)) {
					// Reset the game 
					lander.reset();
					mountain->reset();
					GameMaster::reset();
				}
			}
			else if (GameMaster::gameLost()) {
				// Render "you just lost!"
				Shader::getShader().setUniform1i(1, "gameOver");
				lander.lost();
				mountain->lost();
				shakeTrigger = true;
				glfwSetWindowTitle(window, "Lunar Lander || GAME OVER!");
			}
			else {
				lander.update();
			}

			if (shakeTrigger) {
				if (shakeTimer < 20) {
					shakeTimer++;
					int x, y;
					glfwGetWindowPos(window, &x, &y);
					int new_x = x + (rand() % shakeStrength) - shakeStrength/2;
					int new_y = y + (rand() % shakeStrength) - shakeStrength/2;
					glfwSetWindowPos(window, new_x, new_y);
				}
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
	return 0;
}
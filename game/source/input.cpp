#include"../include/input.h"

#include<GLFW\glfw3.h>

#include<iostream>

Input * Input::m_Instance = nullptr;

Input *Input::instance()
{
	if (m_Instance == nullptr)
		m_Instance = new Input();
	return m_Instance;
}

Input::Input()
{
	glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);

	for (int i = 0; i < 1024; i++) {
		m_Keys[i] = GLFW_RELEASE;
	}
}

bool Input::isKeyDown(int a_Key)
{
	return glfwGetKey(glfwGetCurrentContext(), a_Key) != GLFW_RELEASE;
}

void Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Input *temp = Input::instance();
	temp->m_Keys[key] = action;
}

#pragma once

struct GLFWwindow;

class Input {
private:
	int m_Keys[1024];

	static Input* m_Instance;
	Input();

public:
	static Input* instance();
	
	bool isKeyDown(int a_Key);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
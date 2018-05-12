#pragma once

#include<deque>

enum Type {
	KEY_PRESSED,
	KEY_RELEASED
};

struct Event {
	int type;
	int key;
};

struct GLFWwindow;

class Input {
private:
	int m_Keys[1024];
	std::deque<Event> m_EventPoll;

	static Input* m_Instance;
	Input();

public:
	static Input* instance();
	
	bool isKeyDown(int a_Key);

	std::deque<Event> polledEvents() { return m_EventPoll; }
	void clearPolledEvents() { m_EventPoll.clear(); }
	void pollEvent(Event a_Event) { m_EventPoll.push_back(a_Event); }

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
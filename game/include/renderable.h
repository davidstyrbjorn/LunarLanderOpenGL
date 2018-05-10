#pragma once

#include"vector.h"

// Base class for opengl based drawable object

struct Vertex {
	Vector2 pos;
	Vector4 color;
};

class Renderable {
protected:
	Vector2 m_Pos;
	Vector2 m_Size;
	Vector4 m_Color;

	unsigned int m_VBO; // vertex buffer object
	unsigned int m_VAO; // vertex array object
	unsigned int m_IBO; // index buffer object

public:
	Renderable() : m_Pos(0, 0), m_Color(0, 0, 0, 0) { }

	virtual void draw() { }

	void setPosition(Vector2 a_Pos) { m_Pos = a_Pos; }
	void setColor(Vector4 a_Color) { m_Color = a_Color; }
};
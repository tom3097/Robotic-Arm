#pragma once

#include "GLUT.H"
#include "SimpleOpenGLImageLibrary\src\SOIL.h"
#include <iostream>

class Object
{
public:
	Object(const Object& object) = delete;
	void operator= (const Object& object) = delete;
	static Object& getInstance();
	~Object();
	void display();
	void loadTextures();
private:
	Object();

	GLfloat length;
	GLfloat width;
	GLfloat height;

	void drawBottomQuad();
	void drawTopQuad();
	void drawLeftQuad();
	void drawRightQuad();
	void drawBackQuad();
	void drawFrontQuad();

	const char* textureName;
	GLuint texture;
};


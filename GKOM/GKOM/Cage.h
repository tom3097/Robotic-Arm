#pragma once

#include "GLUT.H"
#include "SimpleOpenGLImageLibrary\src\SOIL.h"
#include <iostream>

#define CAGE_TEXTURES_NO 6
#define LENGTH 100.0
#define WIDTH 100.0
#define HEIGHT 80.0

class Cage
{
public:
	~Cage();
	Cage(const Cage& cage) = delete;
	void operator= (const Cage& cage) = delete;
	static Cage& getInstance();
	void display();
	void loadTextures();
private:
	Cage();

	GLfloat length;
	GLfloat width;
	GLfloat height;

	void drawBottomQuad();
	void drawTopQuad();
	void drawLeftQuad();
	void drawRightQuad();
	void drawBackQuad();
	void drawFrontQuad();

	/*
	 * texture[0] - bottom
	 * texture[1] - top
	 * texture[2] - left
	 * texture[3] - right
	 * texture[4] - back
	 * texture[5] - front
	 */
	const char* textureNames[CAGE_TEXTURES_NO];
	GLuint textures[CAGE_TEXTURES_NO];
};


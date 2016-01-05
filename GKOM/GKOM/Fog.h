#pragma once

#include "GLUT.H"

class Fog
{
public:
	~Fog();
	Fog(const Fog& fog) = delete;
	void operator= (const Fog& fog) = delete;
	static Fog& getInstance();
	void init();
	void keyboard(unsigned char key, int x, int y);
private:
	Fog();

	GLint mode;
	GLfloat density;
	GLfloat color[4];

	bool active;

	void enableDisable();
	void changeMode();
};


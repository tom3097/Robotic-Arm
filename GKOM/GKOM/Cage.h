#pragma once

#include "GLUT.H"

class Cage
{
public:
	~Cage();
	Cage(const Cage& cage) = delete;
	void operator= (const Cage& cage) = delete;
	static Cage& getInstance();
	void display();
private:
	Cage();

	const GLfloat length = 80;
	const GLfloat width = 80;
	const GLfloat height = 80;
};


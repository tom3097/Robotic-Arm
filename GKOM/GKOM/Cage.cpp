#include "Cage.h"



Cage::Cage()
{
}


Cage::~Cage()
{
}


Cage& Cage::getInstance()
{
	static Cage cage;
	return cage;
}


void Cage::display()
{
	glColor3f(1.0, 0.0, 0.0);
	/* Left quad */
	glBegin(GL_QUADS);
	glVertex3f(-length / 2, -height / 2, -width / 2);
	glVertex3f(-length / 2, -height / 2, width / 2);
	glVertex3f(-length / 2, height / 2, width / 2);
	glVertex3f(-length / 2, height / 2, -width / 2);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	/* Right quad */
	glBegin(GL_QUADS);
	glVertex3f(length / 2, -height / 2, -width / 2);
	glVertex3f(length / 2, -height / 2, width / 2);
	glVertex3f(length / 2, height / 2, width / 2);
	glVertex3f(length / 2, height / 2, -width / 2);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	/* Top quad */
	glBegin(GL_QUADS);
	glVertex3f(-length / 2, height / 2, -width / 2);
	glVertex3f(-length / 2, height / 2, width / 2);
	glVertex3f(length / 2, height / 2, width / 2);
	glVertex3f(length / 2, height / 2, -width / 2);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	/* Bottom quad */
	glBegin(GL_QUADS);
	glVertex3f(-length / 2, -height / 2, -width / 2);
	glVertex3f(-length / 2, -height / 2, width / 2);
	glVertex3f(length / 2, -height / 2, width / 2);
	glVertex3f(length / 2, -height / 2, -width / 2);
	glEnd();

	glColor3f(1.0, 0.0, 1.0);
	/* Back quad */
	glBegin(GL_QUADS);
	glVertex3f(length / 2, height / 2, -width / 2);
	glVertex3f(length / 2, -height / 2, -width / 2);
	glVertex3f(-length / 2, -height / 2, -width / 2);
	glVertex3f(-length / 2, height / 2, -width / 2);
	glEnd();

	glColor3f(0.0, 1.0, 1.0);
	/* Front quad */
	glBegin(GL_QUADS);
	glVertex3f(length / 2, height / 2, width / 2);
	glVertex3f(length / 2, -height / 2, width / 2);
	glVertex3f(-length / 2, -height / 2, width / 2);
	glVertex3f(-length / 2, height / 2, width / 2);
	glEnd();
}


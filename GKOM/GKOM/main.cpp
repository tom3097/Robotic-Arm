
/* Projekt z przedmiotu Grafika Komputerowa
 * Temat projektu: Ramie robota
 * Prowadzacy: Mariusz Zubrzycki
 * Autor: Tomasz Bochenski
 */

#define STEP 1.0
#define FRONT_CUT_WALL 10.0
#define BACK_CUT_WALL 200.0
#define VIEWING_ANGLE 60.0

#include "GLUT.H"
#include "Camera.h"
#include "Cage.h"
#include <functional>
#include <iostream>


void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera::getInstance().setView();
	Cage::getInstance().display();

	glFlush();
	glutSwapBuffers();
}


void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(VIEWING_ANGLE, (GLfloat)width / (GLfloat)height, FRONT_CUT_WALL, BACK_CUT_WALL);

	Camera::getInstance().reshape();

	glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y)
{
	static void(Camera::*setVal)(GLfloat) = nullptr;
	static GLfloat(Camera::*getVal)(void) = nullptr;

	switch (key)
	{
	case 'x':
		std::cout << "Button pressed: x.\n";
		setVal = &Camera::setX;
		getVal = &Camera::getX;
		break;
	case 'y':
		std::cout << "Button pressed: y.\n";
		setVal = &Camera::setY;
		getVal = &Camera::getY;
		break;
	case 'z':
		std::cout << "Button pressed: z.\n";
		setVal = &Camera::setZ;
		getVal = &Camera::getZ;
		break;
	case '+':
		std::cout << "Button pressed: +.\n";
		(Camera::getInstance().*setVal)((Camera::getInstance().*getVal)() + 1);
		break;
	case '-':
		std::cout << "Button pressed: -.\n";
		(Camera::getInstance().*setVal)((Camera::getInstance().*getVal)() - 1);
		break;
	default:
		break;
	}

	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


void startProgram(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Robotic-Arm");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutKeyboardFunc(keyboard);

	glutMainLoop();
}


int main(int argc, char** argv)
{
	startProgram(argc, argv);
	return 0;
}
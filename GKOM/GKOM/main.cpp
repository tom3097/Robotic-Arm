
/* Projekt z przedmiotu Grafika Komputerowa
 * Temat projektu: Ramie robota
 * Prowadzacy: Mariusz Zubrzycki
 * Autor: Tomasz Bochenski
 */

#define STEP 1.0
#define FRONT_CUT_WALL 1.0
#define BACK_CUT_WALL 1500.0
#define VIEWING_ANGLE 60.0


#include "GLUT.H"
#include "Camera.h"
#include "Cage.h"
#include "RoboticArm.h"
#include "Object.h"
#include "Light.h"
#include "Fog.h"


void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Camera::getInstance().setView();
	Light::getInstance().display();
	Cage::getInstance().display();
	if (!RoboticArm::getInstance().getManual())
	{
		RoboticArm::getInstance().setInProperPosition();
	}
	RoboticArm::getInstance().display();
	if (!RoboticArm::getInstance().getManual())
	{
		RoboticArm::getInstance().prepareObjectMatrix();
		Object::getInstance().display();
	}

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
	Light::getInstance().keyboard(key, x, y);
	Fog::getInstance().keyboard(key, x, y);
	Camera::getInstance().keyboard(key, x, y);
	RoboticArm::getInstance().keyboard(key, x, y);

	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}


void mouseButton(int button, int state, int x, int y)
{
	Camera::getInstance().mouseButton(button, state,  x, y);
}


void mouseMove(int x, int y)
{
	Camera::getInstance().mouseMove(x, y);
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
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(keyboard);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	Light::getInstance().init();
	Fog::getInstance().init();
	Cage::getInstance().loadTextures();
	RoboticArm::getInstance().loadTextures();
	Object::getInstance().loadTextures();

	glutMainLoop();
}


int main(int argc, char** argv)
{
	startProgram(argc, argv);
	return 0;
}
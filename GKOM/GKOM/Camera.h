#pragma once

#include "GLUT.H"
#include <iostream>

#define INIT_X_DISTANCE 0.0
#define INIT_Y_DISTANCE 30.0
#define INIT_Z_DISTANCE -30.0

class Camera
{
public:
	~Camera();
	Camera(const Camera& camera) = delete;
	void operator= (const Camera& camera) = delete;
	static Camera& getInstance();
	void setView();
	void reshape();
	void setX(GLfloat _x);
	void setY(GLfloat _y);
	void setZ(GLfloat _z);

	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();

	void keyboard(unsigned char key, int x, int y);
	void mouseButton(int button, int state, int x, int y);
	void mouseMove(int x, int y);
private:
	Camera();

	GLfloat x;
	GLfloat y;
	GLfloat z;

	void(Camera::*setVal)(GLfloat);
	GLfloat(Camera::*getVal)(void);

	bool rotationActive;
	int lastX;
	int lastY;
	float rotX;
	float rotY;
};


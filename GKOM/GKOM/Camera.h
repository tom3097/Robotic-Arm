#pragma once

#include "GLUT.H"

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
private:
	Camera();

	GLfloat x;
	GLfloat y;
	GLfloat z;
};


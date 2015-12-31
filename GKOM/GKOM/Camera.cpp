#include "Camera.h"



Camera::Camera() : x(INIT_X_DISTANCE), y(INIT_Y_DISTANCE), z(INIT_Z_DISTANCE), 
setVal(nullptr), getVal(nullptr), lastX(0), lastY(0), rotX(0.0), rotY(0.0), rotationActive(false)
{
}


Camera::~Camera()
{
}


Camera& Camera::getInstance()
{
	static Camera camera;
	return camera;
}


void Camera::setView()
{
	glTranslatef(-x, -y, -z);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glTranslatef(x, y, z);
}


void Camera::reshape()
{
	glTranslatef(x, y, z);
}


void Camera::setX(GLfloat _x)
{
	x = _x;
}


void Camera::setY(GLfloat _y)
{
	y = _y;
}


void Camera::setZ(GLfloat _z)
{
	z = _z;
}


GLfloat Camera::getX()
{
	return x;
}


GLfloat Camera::getY()
{
	return y;
}


GLfloat Camera::getZ()
{
	return z;
}


void Camera::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		setVal = &Camera::setX;
		getVal = &Camera::getX;
		break;
	case 'y':
		setVal = &Camera::setY;
		getVal = &Camera::getY;
		break;
	case 'z':
		setVal = &Camera::setZ;
		getVal = &Camera::getZ;
		break;
	case '+':
		(Camera::getInstance().*setVal)((Camera::getInstance().*getVal)() + 1);
		break;
	case '-':
		(Camera::getInstance().*setVal)((Camera::getInstance().*getVal)() - 1);
		break;
	default:
		break;
	}
}


void Camera::mouseButton(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		rotationActive = false;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		rotationActive = true;
		lastX = x;
		lastY = y;
	}
}


void Camera::mouseMove(int x, int y)
{
	if (rotationActive)
	{
		int deltaX = x - lastX;
		int deltaY = y - lastY;

		lastX = x;
		lastY = y;

		rotX += (float)deltaY;
		rotY += (float)deltaX;
	}
}
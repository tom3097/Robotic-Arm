#include "Camera.h"



Camera::Camera() : x(0.0), y(0.0), z(0.0)
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
	glTranslatef(x, y, z);
}


void Camera::reshape()
{
	setView();
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
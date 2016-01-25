#include "Object.h"


Object::Object()
{
	length = 7;
	width = 5;
	height = 4;

	textureName = "Textures/Object/nyancat.jpg";
}


Object::~Object()
{
}


Object& Object::getInstance()
{
	static Object object;
	return object;
}


void Object::drawBottomQuad()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(-length / 2, -height / 2, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length / 2, -height / 2, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(length / 2, -height / 2, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(length / 2, -height / 2, -width / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Object::drawTopQuad()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0, 0);
	glVertex3f(-length / 2, height / 2, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-length / 2, height / 2, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(length / 2, height / 2, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(length / 2, height / 2, -width / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Object::drawLeftQuad()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(-length / 2, -height / 2, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length / 2, -height / 2, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length / 2, height / 2, width / 2);
	glTexCoord2f(0, 0);
	glVertex3f(-length / 2, height / 2, -width / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Object::drawRightQuad()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0, 1);
	glVertex3f(length / 2, -height / 2, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(length / 2, -height / 2, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(length / 2, height / 2, width / 2);
	glTexCoord2f(0, 0);
	glVertex3f(length / 2, height / 2, -width / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Object::drawBackQuad()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0, 0);
	glVertex3f(length / 2, height / 2, -width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(length / 2, -height / 2, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length / 2, -height / 2, -width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length / 2, height / 2, -width / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Object::drawFrontQuad()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0, 0);
	glVertex3f(length / 2, height / 2, width / 2);
	glTexCoord2f(0, 1);
	glVertex3f(length / 2, -height / 2, width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length / 2, -height / 2, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length / 2, height / 2, width / 2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Object::display()
{
	glColor3f(1.0, 1.0, 1.0);

	drawBottomQuad();
	drawTopQuad();
	drawLeftQuad();
	drawRightQuad();
	drawBackQuad();
	drawFrontQuad();

	glLoadIdentity();
}


void Object::loadTextures()
{
	std::cout << "Loading Object textures..." << std::endl;

	unsigned char* image;
	int width, height;

	glGenTextures(1, &texture);

	image = nullptr;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	image = SOIL_load_image(textureName, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
	{
		std::cerr << "Error while loading texture: " << textureName << std::endl;
		exit(-1);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}

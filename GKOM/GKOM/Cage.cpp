#include "Cage.h"



Cage::Cage() : length(LENGTH), width(WIDTH), height(HEIGHT)
{
	textureNames[0] = "Textures/Cage/bottom.jpg";
	textureNames[1] = "Textures/Cage/top.jpg";
	textureNames[2] = "Textures/Cage/left.jpg";
	textureNames[3] = "Textures/Cage/right.jpg";
	textureNames[4] = "Textures/Cage/back.jpg";
	textureNames[5] = "Textures/Cage/front.jpg";
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
	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	/* Bottom quad */
	glBegin(GL_QUADS);
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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	/* Top quad */
	glBegin(GL_QUADS);
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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	/* Left quad */
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(-length / 2, -height / 2, -width / 2);
	glTexCoord2f(1, 1);
	glVertex3f(-length / 2, -height / 2, width / 2);
	glTexCoord2f(1, 0);
	glVertex3f(-length / 2, height / 2, width / 2);
	glTexCoord2f(0 ,0);
	glVertex3f(-length / 2, height / 2, -width / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	/* Right quad */
	glBegin(GL_QUADS);
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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	/* Back quad */
	glBegin(GL_QUADS);
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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	/* Front quad */
	glBegin(GL_QUADS);
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


void Cage::loadTextures()
{
	std::cout << "Loading textures..." << std::endl;

	unsigned char* image;
	int width, height;

	glGenTextures(6, textures);

	for (int idx = 0; idx < CAGE_TEXTURES_NO; ++idx)
	{
		image = nullptr;

		glBindTexture(GL_TEXTURE_2D, textures[idx]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		image = SOIL_load_image(textureNames[idx], &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
		{
			std::cerr << "Error while loading texture: " << textureNames[idx] << std::endl;
			exit(-1);
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
}
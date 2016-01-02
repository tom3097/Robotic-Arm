#include "RoboticArm.h"



RoboticArm::RoboticArm()
{
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	gluQuadricTexture(quadric, GLU_TRUE);

	textureNames[0] = "Textures/RoboticArm/black.jpg";
	textureNames[1] = "Textures/RoboticArm/gray.jpg";
	textureNames[2] = "Textures/RoboticArm/yellow.jpg";
}


RoboticArm::~RoboticArm()
{
	gluDeleteQuadric(quadric);
}


RoboticArm& RoboticArm::getInstance()
{
	static RoboticArm roboticArm;
	return roboticArm;
}


void RoboticArm::loadTextures()
{
	unsigned char* image;
	int width, height;

	glGenTextures(2, textures);

	for (int idx = 0; idx < ROBOTIC_TEXTURES_NO; ++idx)
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


void RoboticArm::drawWaistPart()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTranslatef(0.0, -40.0, 0.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quadric, WAIST_REGULATOR_RADIUS, WAIST_REGULATOR_RADIUS, WAIST_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0, 0, WAIST_REGULATOR_HEIGHT);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	gluCylinder(quadric, WAIST_ENGINE_RADIUS, WAIST_ENGINE_RADIUS, WAIST_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0, 0, WAIST_ENGINE_HEIGHT);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	gluCylinder(quadric, WAIST_PIECE_RADIUS, WAIST_PIECE_RADIUS, WAIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0, 0, WAIST_PIECE_HEIGHT);
	gluCylinder(quadric, WAIST_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
}


void RoboticArm::drawShoulderPart()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0, SHOULDER_REGULATOR_HEIGHT / 4, -SHOULDER_REGULATOR_HEIGHT / 2);
	gluCylinder(quadric, SHOULDER_REGULATOR_RADIUS, SHOULDER_REGULATOR_RADIUS, SHOULDER_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	gluCylinder(quadric, SHOULDER_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, SHOULDER_REGULATOR_HEIGHT);
	gluCylinder(quadric, SHOULDER_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);


	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTranslatef(0.0, SHOULDER_ENGINE_HEIGHT, 0.0);
	gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, SHOULDER_ENGINE_HEIGHT);
	gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, -(SHOULDER_REGULATOR_HEIGHT + 2 * SHOULDER_ENGINE_HEIGHT));
	gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);


	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 1, 0);
	glTranslatef(0.0, -SHOULDER_ENGINE_HEIGHT / 2, 0.0);
	gluCylinder(quadric, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, -(SHOULDER_REGULATOR_HEIGHT + SHOULDER_ENGINE_HEIGHT), 0.0);
	gluCylinder(quadric, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
}


void RoboticArm::drawElbowPart()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTranslatef(0.0, 0.0, SHOULDER_PIECE_HEIGHT);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0, 0.0, -(SHOULDER_REGULATOR_HEIGHT + 1.5 * SHOULDER_ENGINE_HEIGHT));
	gluCylinder(quadric, ELBOW_REGULATOR_RADIUS, ELBOW_REGULATOR_RADIUS, ELBOW_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	gluCylinder(quadric, ELBOW_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, ELBOW_REGULATOR_HEIGHT);
	gluCylinder(quadric, ELBOW_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTranslatef(0.0, 0.0, -(ELBOW_REGULATOR_HEIGHT / 2 + ELBOW_ENGINE_HEIGHT / 2));
	gluCylinder(quadric, ELBOW_ENGINE_RADIUS, ELBOW_ENGINE_RADIUS, ELBOW_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	gluCylinder(quadric, ELBOW_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, ELBOW_ENGINE_HEIGHT);
	gluCylinder(quadric, ELBOW_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glRotatef(-90, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0.0, ELBOW_ENGINE_HEIGHT / 2, 0.0);
	gluCylinder(quadric, ELBOW_PIECE_RADIUS, ELBOW_PIECE_RADIUS, ELBOW_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
}


void RoboticArm::drawWristPart()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTranslatef(0.0, 0.0, ELBOW_PIECE_HEIGHT);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT / 2);
	gluCylinder(quadric, FIRST_WRIST_REGULATOR_RADIUS, FIRST_WRIST_REGULATOR_RADIUS, FIRST_WRIST_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, FIRST_WRIST_REGULATOR_HEIGHT);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTranslatef(0.0, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT);
	gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, FIRST_WRIST_ENGINE_HEIGHT);
	gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, FIRST_WRIST_REGULATOR_HEIGHT - 2 * FIRST_WRIST_ENGINE_HEIGHT);
	gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, FIRST_WRIST_ENGINE_HEIGHT);
	gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glRotatef(-90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	glTranslatef(FIRST_WRIST_ENGINE_HEIGHT / 2 - FIRST_WRIST_REGULATOR_HEIGHT, 0.0, 0.0);
	gluCylinder(quadric, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(FIRST_WRIST_REGULATOR_HEIGHT - FIRST_WRIST_ENGINE_HEIGHT, 0.0, 0.0);
	gluCylinder(quadric, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-FIRST_WRIST_PIECE_HEIGHT, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT + FIRST_WRIST_PIECE_RADIUS / 2);
	gluCylinder(quadric, SECOND_WRIST_PIECE_RADIUS, SECOND_WRIST_PIECE_RADIUS, SECOND_WRIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	gluCylinder(quadric, SECOND_WRIST_PIECE_RADIUS, 0.0, 0, SUBDIVISIONS, SUBDIVISIONS);
	glTranslatef(0.0, 0.0, SECOND_WRIST_PIECE_HEIGHT);
	gluCylinder(quadric, SECOND_WRIST_PIECE_RADIUS, 0.0, 0, SUBDIVISIONS, SUBDIVISIONS);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-SECOND_WRIST_PIECE_HEIGHT / 2, 0, 0.0);
	gluCylinder(quadric, SECOND_WRIST_REGULATOR_RADIUS, SECOND_WRIST_REGULATOR_RADIUS, SECOND_WRIST_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTranslatef(0, 0, SECOND_WRIST_ENGINE_RADIUS + SECOND_WRIST_REGULATOR_RADIUS);
	gluSphere(quadric, SECOND_WRIST_ENGINE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
}


void RoboticArm::drawToolPart()
{
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0.0, SECOND_WRIST_ENGINE_RADIUS, -TOOL_PIECE_HEIGHT / 2);
	gluCylinder(quadric, TOOL_PIECE_RADIUS, TOOL_PIECE_RADIUS, TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
}


void RoboticArm::display()
{
	glColor3f(1.0, 1.0, 1.0);

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	drawWaistPart();
	drawShoulderPart();
	drawElbowPart();
	drawWristPart();
	drawToolPart();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}


void RoboticArm::keyboard(unsigned char key, int x, int y)
{
	/* @toDO */
}
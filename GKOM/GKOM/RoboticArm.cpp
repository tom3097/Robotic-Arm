#include "RoboticArm.h"



RoboticArm::RoboticArm() : setVal(nullptr), getVal(nullptr), waistAngle(0.0), shoulderAngle(0.0), elbowAngle(0.0),
cylinderWristAngle(0.0), sphereWristAngle(0.0), toolAngle(0.0), counterVal(0), manual(false)
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
	std::cout << "Loading Robot textures..." << std::endl;

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


void RoboticArm::setWaistAngle(GLfloat _waistAngle)
{
	waistAngle = _waistAngle;
}


void RoboticArm::setShoulderAngle(GLfloat _shoulderAngle)
{
	shoulderAngle = _shoulderAngle;
}


void RoboticArm::setElbowAngle(GLfloat _elbowAngle)
{
	elbowAngle = _elbowAngle;
}


void RoboticArm::setCylinderWristAngle(GLfloat _cylinderWristAngle)
{
	cylinderWristAngle = _cylinderWristAngle;
}


void RoboticArm::setSphereWristAngle(GLfloat _sphereWristAngle)
{
	sphereWristAngle = _sphereWristAngle;
}


void RoboticArm::setToolAngle(GLfloat _toolAngle)
{
	toolAngle = _toolAngle;
}


GLfloat RoboticArm::getWaistAngle()
{
	return waistAngle;
}


GLfloat RoboticArm::getShoulderAngle()
{
	return shoulderAngle;
}


GLfloat RoboticArm::getElbowAngle()
{
	return elbowAngle;
}


GLfloat RoboticArm::getCylinderWristAngle()
{
	return cylinderWristAngle;
}


GLfloat RoboticArm::getSphereWristAngle()
{
	return sphereWristAngle;
}


GLfloat RoboticArm::getToolAngle()
{
	return toolAngle;
}


void RoboticArm::drawWaistPart()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glTranslatef(0.0, -CAGE_HEIGHT / 2, 0.0);
		glRotatef(-90, 1, 0, 0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		gluCylinder(quadric, WAIST_REGULATOR_RADIUS, WAIST_REGULATOR_RADIUS, WAIST_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0, 0, WAIST_REGULATOR_HEIGHT);
		glRotatef(waistAngle, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		gluCylinder(quadric, WAIST_ENGINE_RADIUS, WAIST_ENGINE_RADIUS, WAIST_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0, 0, WAIST_ENGINE_HEIGHT);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		gluCylinder(quadric, WAIST_PIECE_RADIUS, WAIST_PIECE_RADIUS, WAIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0, 0, WAIST_PIECE_HEIGHT);
		gluCylinder(quadric, WAIST_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


void RoboticArm::drawShoulderPart()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glRotated(waistAngle, 0, 1, 0);
		glTranslatef(0.0, -CAGE_HEIGHT / 2 + WAIST_REGULATOR_HEIGHT + WAIST_ENGINE_HEIGHT + WAIST_PIECE_HEIGHT, 0.0);
		glTranslatef(0.0, SHOULDER_REGULATOR_HEIGHT / 4, -SHOULDER_REGULATOR_HEIGHT / 2);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		gluCylinder(quadric, SHOULDER_REGULATOR_RADIUS, SHOULDER_REGULATOR_RADIUS, SHOULDER_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, SHOULDER_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, SHOULDER_REGULATOR_HEIGHT);
		gluCylinder(quadric, SHOULDER_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0.0, SHOULDER_ENGINE_HEIGHT, 0.0);
		glRotatef(shoulderAngle, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, SHOULDER_ENGINE_HEIGHT);
		gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0.0, 0.0, -(SHOULDER_REGULATOR_HEIGHT + 2 * SHOULDER_ENGINE_HEIGHT));
		gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_RADIUS, SHOULDER_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, SHOULDER_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glRotatef(-90, 1, 0, 0);
		glRotatef(45, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glTranslatef(0.0, -SHOULDER_ENGINE_HEIGHT / 2, 0.0);
		gluCylinder(quadric, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0.0, -(SHOULDER_REGULATOR_HEIGHT + SHOULDER_ENGINE_HEIGHT), 0.0);
		gluCylinder(quadric, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_RADIUS, SHOULDER_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}


void RoboticArm::drawElbowPart()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glRotated(waistAngle, 0, 1, 0);
		glTranslatef(0.0, -CAGE_HEIGHT / 2 + WAIST_REGULATOR_HEIGHT + WAIST_ENGINE_HEIGHT + WAIST_PIECE_HEIGHT, 0.0);
		glTranslatef(0.0, SHOULDER_REGULATOR_HEIGHT / 4 + SHOULDER_ENGINE_HEIGHT, SHOULDER_REGULATOR_HEIGHT / 2);
		glRotatef(shoulderAngle, 0, 0, 1);
		glTranslatef(0.0, 0.0, -SHOULDER_REGULATOR_HEIGHT - SHOULDER_ENGINE_HEIGHT);
		glRotatef(-45, 0, 0, 1);
		glTranslatef(0.0, SHOULDER_PIECE_HEIGHT, 0.0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		gluCylinder(quadric, ELBOW_REGULATOR_RADIUS, ELBOW_REGULATOR_RADIUS, ELBOW_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, ELBOW_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, ELBOW_REGULATOR_HEIGHT);
		gluCylinder(quadric, ELBOW_REGULATOR_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0.0, 0.0, -(ELBOW_REGULATOR_HEIGHT / 2 + ELBOW_ENGINE_HEIGHT / 2));
		glRotatef(elbowAngle, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		gluCylinder(quadric, ELBOW_ENGINE_RADIUS, ELBOW_ENGINE_RADIUS, ELBOW_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, ELBOW_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, ELBOW_ENGINE_HEIGHT);
		gluCylinder(quadric, ELBOW_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glRotatef(-90, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glTranslatef(0.0, ELBOW_ENGINE_HEIGHT / 2, 0.0);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		gluCylinder(quadric, ELBOW_PIECE_RADIUS, ELBOW_PIECE_RADIUS, ELBOW_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


void RoboticArm::drawWristPart()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glRotated(waistAngle, 0, 1, 0);
		glTranslatef(0.0, -CAGE_HEIGHT / 2 + WAIST_REGULATOR_HEIGHT + WAIST_ENGINE_HEIGHT + WAIST_PIECE_HEIGHT, 0.0);
		glTranslatef(0.0, SHOULDER_REGULATOR_HEIGHT / 4 + SHOULDER_ENGINE_HEIGHT, SHOULDER_REGULATOR_HEIGHT / 2);
		glRotatef(shoulderAngle, 0, 0, 1);
		glTranslatef(0.0, 0.0, -SHOULDER_REGULATOR_HEIGHT - SHOULDER_ENGINE_HEIGHT);
		glRotatef(-45, 0, 0, 1);
		glTranslatef(0.0, SHOULDER_PIECE_HEIGHT, ELBOW_REGULATOR_HEIGHT / 2 - ELBOW_ENGINE_HEIGHT / 2);
		glRotatef(elbowAngle, 0, 0, 1);
		glTranslatef(-ELBOW_PIECE_HEIGHT, 0.0, ELBOW_ENGINE_HEIGHT / 2);
		glTranslatef(0.0, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT / 2);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		gluCylinder(quadric, FIRST_WRIST_REGULATOR_RADIUS, FIRST_WRIST_REGULATOR_RADIUS, FIRST_WRIST_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0.0, 0.0, FIRST_WRIST_REGULATOR_HEIGHT);
		glTranslatef(0.0, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT);
		glRotatef(cylinderWristAngle, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, FIRST_WRIST_ENGINE_HEIGHT);
		gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0.0, 0.0, FIRST_WRIST_REGULATOR_HEIGHT - 2 * FIRST_WRIST_ENGINE_HEIGHT);
		gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_RADIUS, FIRST_WRIST_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, FIRST_WRIST_ENGINE_HEIGHT);
		gluCylinder(quadric, FIRST_WRIST_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glRotatef(-90, 0, 1, 0);
		glRotatef(45, 1, 0, 0);
		glTranslatef(FIRST_WRIST_ENGINE_HEIGHT / 2 - FIRST_WRIST_REGULATOR_HEIGHT, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		gluCylinder(quadric, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(FIRST_WRIST_REGULATOR_HEIGHT - FIRST_WRIST_ENGINE_HEIGHT, 0.0, 0.0);
		gluCylinder(quadric, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_RADIUS, FIRST_WRIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

		glRotatef(90, 0, 1, 0);
		glTranslatef(-FIRST_WRIST_PIECE_HEIGHT, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT + FIRST_WRIST_PIECE_RADIUS / 2);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		gluCylinder(quadric, SECOND_WRIST_PIECE_RADIUS, SECOND_WRIST_PIECE_RADIUS, SECOND_WRIST_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, SECOND_WRIST_PIECE_RADIUS, 0.0, 0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, SECOND_WRIST_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_WRIST_PIECE_RADIUS, 0.0, 0, SUBDIVISIONS, SUBDIVISIONS);

		glRotatef(-90, 0, 1, 0);
		glTranslatef(-SECOND_WRIST_PIECE_HEIGHT / 2, 0, 0.0);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		gluCylinder(quadric, SECOND_WRIST_REGULATOR_RADIUS, SECOND_WRIST_REGULATOR_RADIUS, SECOND_WRIST_REGULATOR_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);

		glRotatef(sphereWristAngle, 0, 0, 1);
		glTranslatef(0, 0, SECOND_WRIST_ENGINE_RADIUS + SECOND_WRIST_REGULATOR_RADIUS);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		gluSphere(quadric, SECOND_WRIST_ENGINE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


void RoboticArm::drawToolPart()
{
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
		glRotated(waistAngle, 0, 1, 0);
		glTranslatef(0.0, -CAGE_HEIGHT / 2 + WAIST_REGULATOR_HEIGHT + WAIST_ENGINE_HEIGHT + WAIST_PIECE_HEIGHT, 0.0);
		glTranslatef(0.0, SHOULDER_REGULATOR_HEIGHT / 4 + SHOULDER_ENGINE_HEIGHT, SHOULDER_REGULATOR_HEIGHT / 2);
		glRotatef(shoulderAngle, 0, 0, 1);
		glTranslatef(0.0, 0.0, -SHOULDER_REGULATOR_HEIGHT - SHOULDER_ENGINE_HEIGHT);
		glRotatef(-45, 0, 0, 1);
		glTranslatef(0.0, SHOULDER_PIECE_HEIGHT, ELBOW_REGULATOR_HEIGHT / 2 - ELBOW_ENGINE_HEIGHT / 2);
		glRotatef(elbowAngle, 0, 0, 1);
		glTranslatef(-ELBOW_PIECE_HEIGHT, 0.0, ELBOW_ENGINE_HEIGHT / 2 - FIRST_WRIST_REGULATOR_HEIGHT / 2);
		glRotatef(cylinderWristAngle, 0, 0, 1);
		glTranslatef(0.0, 0.0, FIRST_WRIST_REGULATOR_HEIGHT);
		glRotatef(45, 0, 0, 1);
		glTranslatef(0.0, 0.0, SECOND_WRIST_PIECE_HEIGHT - FIRST_WRIST_ENGINE_HEIGHT / 2 - SECOND_WRIST_PIECE_HEIGHT / 2);
		glTranslatef(-FIRST_WRIST_PIECE_HEIGHT, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT + FIRST_WRIST_PIECE_RADIUS / 2);
		glRotatef(-sphereWristAngle, 1, 0, 0);
		glTranslatef(-SECOND_WRIST_ENGINE_RADIUS - SECOND_WRIST_REGULATOR_RADIUS, 0, 0.0);

		glRotatef(-90, 0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0.0, SECOND_WRIST_ENGINE_RADIUS, -FIRST_TOOL_PIECE_HEIGHT / 2);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		gluCylinder(quadric, FIRST_TOOL_PIECE_RADIUS, FIRST_TOOL_PIECE_RADIUS, FIRST_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, FIRST_TOOL_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslated(0.0, 0.0, FIRST_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, FIRST_TOOL_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glRotatef(90, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);

		glTranslatef(-SECOND_TOOL_PIECE_RADIUS, -FIRST_TOOL_PIECE_RADIUS, -SECOND_TOOL_PIECE_RADIUS);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluSphere(quadric, FIRST_SPHERE_TOOL_PIECE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, SECOND_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0, 2 * FIRST_TOOL_PIECE_RADIUS, -SECOND_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluSphere(quadric, FIRST_SPHERE_TOOL_PIECE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, SECOND_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glTranslated(FIRST_TOOL_PIECE_HEIGHT + 2 * SECOND_TOOL_PIECE_RADIUS, 0, -SECOND_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluSphere(quadric, FIRST_SPHERE_TOOL_PIECE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, SECOND_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0, -2 * FIRST_TOOL_PIECE_RADIUS, -SECOND_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluSphere(quadric, FIRST_SPHERE_TOOL_PIECE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, SECOND_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, SECOND_TOOL_PIECE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, -SECOND_TOOL_PIECE_HEIGHT);

		glTranslatef(0, TOOL_ENGINE_HEIGHT / 2 + FIRST_TOOL_PIECE_RADIUS / 2 + SECOND_TOOL_PIECE_RADIUS, SECOND_TOOL_PIECE_HEIGHT);
		glTranslatef(0.0, FIRST_SPHERE_TOOL_PIECE_RADIUS / 4, 0.0);
		glRotatef(90, 1, 0, 0);
		glRotatef(toolAngle, 0, 0, 1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		gluCylinder(quadric, TOOL_ENGINE_RADIUS, TOOL_ENGINE_RADIUS, TOOL_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, TOOL_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, TOOL_ENGINE_HEIGHT);
		gluCylinder(quadric, TOOL_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glRotatef(-toolAngle, 0, 0, 1);

		glTranslatef(-FIRST_TOOL_PIECE_HEIGHT - 2 * SECOND_TOOL_PIECE_RADIUS, 0.0, -TOOL_ENGINE_HEIGHT);
		glRotatef(-toolAngle, 0, 0, 1);
		gluCylinder(quadric, TOOL_ENGINE_RADIUS, TOOL_ENGINE_RADIUS, TOOL_ENGINE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		gluCylinder(quadric, TOOL_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, TOOL_ENGINE_HEIGHT);
		gluCylinder(quadric, TOOL_ENGINE_RADIUS, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glRotatef(toolAngle, 0, 0, 1);

		glRotatef(-90, 1, 0, 0);
		glRotatef(-30, 0, 1, 0);
		glRotatef(toolAngle, 0, 1, 0);
		glTranslatef(0.0, TOOL_ENGINE_HEIGHT / 2, TOOL_ENGINE_RADIUS / 2);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		gluCylinder(quadric, THIRD_TOOL_PIECE_RADIUS_MAX, THIRD_TOOL_PIECE_RADIUS_MIN, THIRD_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, THIRD_TOOL_PIECE_HEIGHT);
		gluSphere(quadric, SECOND_SPHERE_TOOL_PIECE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
		glRotatef(65, 0, 1, 0);
		gluCylinder(quadric, FOURTH_TOOL_PIECE_RADIUS_MAX, FOURTH_TOOL_PIECE_RADIUS_MIN, FOURTH_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, FOURTH_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, FOURTH_TOOL_PIECE_RADIUS_MIN, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);

		glTranslatef(0.0, 0.0, -FOURTH_TOOL_PIECE_HEIGHT);
		glRotatef(-65, 0, 1, 0);
		glTranslatef(0.0, 0.0, -THIRD_TOOL_PIECE_HEIGHT);
		glTranslatef(0.0, -TOOL_ENGINE_HEIGHT / 2, -TOOL_ENGINE_RADIUS / 2);
		glRotatef(-toolAngle, 0, 1, 0);
		glRotatef(30, 0, 1, 0);
		glTranslatef(FIRST_TOOL_PIECE_HEIGHT + 2 * SECOND_TOOL_PIECE_RADIUS, 0.0, 0.0);
		glRotatef(30, 0, 1, 0);
		glRotatef(-toolAngle, 0, 1, 0);
		glTranslatef(0.0, TOOL_ENGINE_HEIGHT / 2, TOOL_ENGINE_RADIUS / 2);
		gluCylinder(quadric, THIRD_TOOL_PIECE_RADIUS_MAX, THIRD_TOOL_PIECE_RADIUS_MIN, THIRD_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, THIRD_TOOL_PIECE_HEIGHT);
		gluSphere(quadric, SECOND_SPHERE_TOOL_PIECE_RADIUS, SUBDIVISIONS, SUBDIVISIONS);
		glRotatef(-65, 0, 1, 0);
		gluCylinder(quadric, FOURTH_TOOL_PIECE_RADIUS_MAX, FOURTH_TOOL_PIECE_RADIUS_MIN, FOURTH_TOOL_PIECE_HEIGHT, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, FOURTH_TOOL_PIECE_HEIGHT);
		gluCylinder(quadric, FOURTH_TOOL_PIECE_RADIUS_MIN, 0.0, 0.0, SUBDIVISIONS, SUBDIVISIONS);
		glTranslatef(0.0, 0.0, -FOURTH_TOOL_PIECE_HEIGHT);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}


void RoboticArm::display()
{
	glColor3f(1.0, 1.0, 1.0);

	drawWaistPart();
	drawShoulderPart();
	drawElbowPart();
	drawWristPart();
	drawToolPart();
}


void RoboticArm::keyboard(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		manual = !manual;
		counterVal = 0;
		waistAngle = 0;
		shoulderAngle = 0;
		elbowAngle = 0;
		cylinderWristAngle = 0;
		sphereWristAngle = 0;
		toolAngle = 0;
		return;
	}

	if (!manual)
		return;

	switch (key)
	{
	case '1':
		setVal = &RoboticArm::setWaistAngle;
		getVal = &RoboticArm::getWaistAngle;
		break;
	case '2':
		setVal = &RoboticArm::setShoulderAngle;
		getVal = &RoboticArm::getShoulderAngle;
		break;
	case '3':
		setVal = &RoboticArm::setElbowAngle;
		getVal = &RoboticArm::getElbowAngle;
		break;
	case '4':
		setVal = &RoboticArm::setCylinderWristAngle;
		getVal = &RoboticArm::getCylinderWristAngle;
		break;
	case '5':
		setVal = &RoboticArm::setSphereWristAngle;
		getVal = &RoboticArm::getSphereWristAngle;
		break;
	case '6':
		setVal = &RoboticArm::setToolAngle;
		getVal = &RoboticArm::getToolAngle;
		break;
	case 'i':
		(RoboticArm::getInstance().*setVal)((RoboticArm::getInstance().*getVal)() + 1);
		break;
	case 'd':
		(RoboticArm::getInstance().*setVal)((RoboticArm::getInstance().*getVal)() - 1);
		break;
	default:
		break;
	}
}


void RoboticArm::setInProperPosition()
{
	if (++counterVal > MAX_COUNTER_VAL)
		counterVal = 1;

	if (counterVal <= 1800)
	{
		waistAngle = waistAngle + 0.1;
		shoulderAngle = shoulderAngle + 0.05;
		elbowAngle = elbowAngle - 0.0145;
		cylinderWristAngle = cylinderWristAngle + 0.0145;
		sphereWristAngle = sphereWristAngle + 0.025;
		toolAngle = toolAngle - 0.033;
	}
	else if (counterVal <= 2200)
	{
		toolAngle = toolAngle + 0.12;
	}
	else if (counterVal <= 4000)
	{
		waistAngle = waistAngle - 0.1;
		shoulderAngle = shoulderAngle - 0.05;
		elbowAngle = elbowAngle + 0.0145;
		cylinderWristAngle = cylinderWristAngle - 0.0145;
		sphereWristAngle = sphereWristAngle - 0.025;
	}
	else if (counterVal <= 4900)
	{
		waistAngle = waistAngle - 0.1;
		shoulderAngle = shoulderAngle + 0.131;
		elbowAngle = elbowAngle - 0.182;
		cylinderWristAngle = cylinderWristAngle + 0.053;
		sphereWristAngle = sphereWristAngle - 0.153;
	}
	else if (counterVal <= 5800)
	{
		waistAngle = waistAngle + 0.1;
		shoulderAngle = shoulderAngle - 0.131;
		elbowAngle = elbowAngle + 0.182;
		cylinderWristAngle = cylinderWristAngle - 0.053;
		sphereWristAngle = sphereWristAngle + 0.153;
	}
	else if (counterVal <= 7600)
	{
		waistAngle = waistAngle + 0.1;
		shoulderAngle = shoulderAngle + 0.05;
		elbowAngle = elbowAngle - 0.0145;
		cylinderWristAngle = cylinderWristAngle + 0.0145;
		sphereWristAngle = sphereWristAngle + 0.025;
	}
	else if (counterVal <= 8000)
	{
		toolAngle = toolAngle - 0.12;
	}
	else if (counterVal <= 9800)
	{
		waistAngle = waistAngle - 0.1;
		shoulderAngle = shoulderAngle - 0.05;
		elbowAngle = elbowAngle + 0.0145;
		cylinderWristAngle = cylinderWristAngle - 0.0145;
		sphereWristAngle = sphereWristAngle - 0.025;
		toolAngle = toolAngle + 0.033;
	}
}


void RoboticArm::prepareMotionMatrix()
{
	glRotated(waistAngle, 0, 1, 0);
	glTranslatef(0.0, -CAGE_HEIGHT / 2 + WAIST_REGULATOR_HEIGHT + WAIST_ENGINE_HEIGHT + WAIST_PIECE_HEIGHT, 0.0);
	glTranslatef(0.0, SHOULDER_REGULATOR_HEIGHT / 4 + SHOULDER_ENGINE_HEIGHT, SHOULDER_REGULATOR_HEIGHT / 2);
	glRotatef(shoulderAngle, 0, 0, 1);
	glTranslatef(0.0, 0.0, -SHOULDER_REGULATOR_HEIGHT - SHOULDER_ENGINE_HEIGHT);
	glRotatef(-45, 0, 0, 1);
	glTranslatef(0.0, SHOULDER_PIECE_HEIGHT, ELBOW_REGULATOR_HEIGHT / 2 - ELBOW_ENGINE_HEIGHT / 2);
	glRotatef(elbowAngle, 0, 0, 1);
	glTranslatef(-ELBOW_PIECE_HEIGHT, 0.0, ELBOW_ENGINE_HEIGHT / 2 - FIRST_WRIST_REGULATOR_HEIGHT / 2);
	glRotatef(cylinderWristAngle, 0, 0, 1);
	glTranslatef(0.0, 0.0, FIRST_WRIST_REGULATOR_HEIGHT);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0.0, 0.0, SECOND_WRIST_PIECE_HEIGHT - FIRST_WRIST_ENGINE_HEIGHT / 2 - SECOND_WRIST_PIECE_HEIGHT / 2);
	glTranslatef(-FIRST_WRIST_PIECE_HEIGHT, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT + FIRST_WRIST_PIECE_RADIUS / 2);
	glRotatef(-sphereWristAngle, 1, 0, 0);
	glTranslatef(-SECOND_WRIST_ENGINE_RADIUS - SECOND_WRIST_REGULATOR_RADIUS, 0, 0.0);
	glTranslatef(-7, 0.0, 0.0);
	glRotatef(90, 0.0, 1, 0);
}


void RoboticArm::prepareNoMotionMatrix()
{
	glRotated(180, 0, 1, 0);
	glTranslatef(0.0, -CAGE_HEIGHT / 2 + WAIST_REGULATOR_HEIGHT + WAIST_ENGINE_HEIGHT + WAIST_PIECE_HEIGHT, 0.0);
	glTranslatef(0.0, SHOULDER_REGULATOR_HEIGHT / 4 + SHOULDER_ENGINE_HEIGHT, SHOULDER_REGULATOR_HEIGHT / 2);
	glRotatef(90, 0, 0, 1);
	glTranslatef(0.0, 0.0, -SHOULDER_REGULATOR_HEIGHT - SHOULDER_ENGINE_HEIGHT);
	glRotatef(-45, 0, 0, 1);
	glTranslatef(0.0, SHOULDER_PIECE_HEIGHT, ELBOW_REGULATOR_HEIGHT / 2 - ELBOW_ENGINE_HEIGHT / 2);
	glRotatef(-26, 0, 0, 1);
	glTranslatef(-ELBOW_PIECE_HEIGHT, 0.0, ELBOW_ENGINE_HEIGHT / 2 - FIRST_WRIST_REGULATOR_HEIGHT / 2);
	glRotatef(26, 0, 0, 1);
	glTranslatef(0.0, 0.0, FIRST_WRIST_REGULATOR_HEIGHT);
	glRotatef(45, 0, 0, 1);
	glTranslatef(0.0, 0.0, SECOND_WRIST_PIECE_HEIGHT - FIRST_WRIST_ENGINE_HEIGHT / 2 - SECOND_WRIST_PIECE_HEIGHT / 2);
	glTranslatef(-FIRST_WRIST_PIECE_HEIGHT, 0.0, -FIRST_WRIST_REGULATOR_HEIGHT + FIRST_WRIST_PIECE_RADIUS / 2);
	glRotatef(-45, 1, 0, 0);
	glTranslatef(-SECOND_WRIST_ENGINE_RADIUS - SECOND_WRIST_REGULATOR_RADIUS, 0, 0.0);
	glTranslatef(-7, 0.0, 0.0);
	glRotatef(90, 0.0, 1, 0);
}


void RoboticArm::prepareObjectMatrix()
{
	if (counterVal <= 2200)
		prepareNoMotionMatrix();
	else if (counterVal <= 7600)
		prepareMotionMatrix();
	else if (counterVal <= 9800)
		prepareNoMotionMatrix();
}


bool RoboticArm::getManual()
{
	return manual;
}
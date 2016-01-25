#pragma once

#include "GLUT.H"
#include <iostream>
#include "SimpleOpenGLImageLibrary\src\SOIL.h"
#include "Object.h"

#define ROBOTIC_TEXTURES_NO 3

#define SCALE 1.4
#define CAGE_HEIGHT 80.0
#define SUBDIVISIONS (16 * SCALE)

/* Waist part macros */
#define WAIST_ENGINE_RADIUS (4.0 * SCALE)
#define WAIST_ENGINE_HEIGHT (0.7 * SCALE)
#define WAIST_REGULATOR_RADIUS WAIST_ENGINE_RADIUS
#define WAIST_REGULATOR_HEIGHT WAIST_ENGINE_HEIGHT
#define WAIST_PIECE_RADIUS WAIST_ENGINE_RADIUS
#define WAIST_PIECE_HEIGHT WAIST_ENGINE_HEIGHT

/* Shoulder part macros */
#define SHOULDER_ENGINE_RADIUS (0.85 * SCALE)
#define SHOULDER_ENGINE_HEIGHT (1.5 * SCALE)
#define SHOULDER_REGULATOR_RADIUS (2.5 * SCALE)
#define SHOULDER_REGULATOR_HEIGHT (2.0 * SCALE)
#define SHOULDER_PIECE_RADIUS (0.55 * SCALE)
#define SHOULDER_PIECE_HEIGHT (12.0 * SCALE)

/* Elbow part macros */
#define ELBOW_ENGINE_RADIUS (0.85 * SCALE)
#define ELBOW_ENGINE_HEIGHT (2.0 * SCALE)
#define ELBOW_REGULATOR_RADIUS (0.7 * SCALE)
#define ELBOW_REGULATOR_HEIGHT (2 * SHOULDER_ENGINE_HEIGHT + SHOULDER_REGULATOR_HEIGHT)
#define ELBOW_PIECE_RADIUS (0.6 * SCALE)
#define ELBOW_PIECE_HEIGHT (9.0 * SCALE)

/* Wrist part macros */
#define FIRST_WRIST_ENGINE_RADIUS (0.85 * SCALE)
#define FIRST_WRIST_ENGINE_HEIGHT (1.3 * SCALE)
#define FIRST_WRIST_REGULATOR_RADIUS (0.7 * SCALE)
#define FIRST_WRIST_REGULATOR_HEIGHT (ELBOW_REGULATOR_HEIGHT - (1.0 * SCALE))
#define FIRST_WRIST_PIECE_RADIUS (0.3 * SCALE)
#define FIRST_WRIST_PIECE_HEIGHT (1.5 * SCALE)
#define SECOND_WRIST_ENGINE_RADIUS (1.0 * SCALE)
#define SECOND_WRIST_REGULATOR_RADIUS (0.4 * SCALE)
#define SECOND_WRIST_REGULATOR_HEIGHT (1.0 * SCALE)
#define SECOND_WRIST_PIECE_RADIUS (0.4 * SCALE)
#define SECOND_WRIST_PIECE_HEIGHT ELBOW_REGULATOR_HEIGHT

/* Tool part macros */
#define FIRST_TOOL_PIECE_RADIUS (0.3 * SCALE)
#define FIRST_TOOL_PIECE_HEIGHT (2.5 * SCALE)
#define SECOND_TOOL_PIECE_RADIUS (0.1 * SCALE)
#define SECOND_TOOL_PIECE_HEIGHT (1.0 * SCALE)
#define FIRST_SPHERE_TOOL_PIECE_RADIUS (0.2 * SCALE)
#define TOOL_ENGINE_RADIUS (0.4 * SCALE)
#define TOOL_ENGINE_HEIGHT (0.6 * SCALE)
#define THIRD_TOOL_PIECE_RADIUS_MAX (0.3 * SCALE)
#define THIRD_TOOL_PIECE_RADIUS_MIN (0.2 * SCALE)
#define THIRD_TOOL_PIECE_HEIGHT (1.5 * SCALE)
#define SECOND_SPHERE_TOOL_PIECE_RADIUS (0.3 * SCALE)
#define FOURTH_TOOL_PIECE_RADIUS_MAX (0.25 * SCALE)
#define FOURTH_TOOL_PIECE_RADIUS_MIN (0.1 * SCALE)
#define FOURTH_TOOL_PIECE_HEIGHT (2.5 * SCALE)


#define MAX_COUNTER_VAL 9800


class RoboticArm
{
public:
	~RoboticArm();
	RoboticArm(const RoboticArm& roboticArm) = delete;
	void operator= (const RoboticArm& roboticArm) = delete;
	static RoboticArm& getInstance();
	void loadTextures();
	void display();
	void keyboard(unsigned char key, int x, int y);

	void setWaistAngle(GLfloat _waistAngle);
	void setShoulderAngle(GLfloat _shoulderAngle);
	void setElbowAngle(GLfloat _elbowAngle);
	void setCylinderWristAngle(GLfloat _cylinderWristAngle);
	void setSphereWristAngle(GLfloat _sphereWristAngle);
	void setToolAngle(GLfloat _toolAngle);

	bool getManual();

	GLfloat getWaistAngle();
	GLfloat getShoulderAngle();
	GLfloat getElbowAngle();
	GLfloat getCylinderWristAngle();
	GLfloat getSphereWristAngle();
	GLfloat getToolAngle();

	void setInProperPosition();
	void prepareObjectMatrix();
private:
	RoboticArm();

	void drawWaistPart();
	void drawShoulderPart();
	void drawElbowPart();
	void drawWristPart();
	void drawToolPart();


	void prepareMotionMatrix();
	void prepareNoMotionMatrix();

	void(RoboticArm::*setVal)(GLfloat);
	GLfloat(RoboticArm::*getVal)(void);

	GLUquadric *quadric;

	GLfloat waistAngle;
	GLfloat shoulderAngle;
	GLfloat elbowAngle;
	GLfloat cylinderWristAngle;
	GLfloat sphereWristAngle;
	GLfloat toolAngle;

	bool manual;
	int counterVal;

	const char* textureNames[ROBOTIC_TEXTURES_NO];
	GLuint textures[ROBOTIC_TEXTURES_NO];
};


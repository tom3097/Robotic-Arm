#pragma once

#include "GLUT.H"
#include <iostream>
#include "SimpleOpenGLImageLibrary\src\SOIL.h"

#define ROBOTIC_TEXTURES_NO 3

#define SCALE 1.7
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
#define TOOL_PIECE_RADIUS (0.2 * SCALE)
#define TOOL_PIECE_HEIGHT (2.5 * SCALE)

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
private:
	RoboticArm();

	void drawWaistPart();
	void drawShoulderPart();
	void drawElbowPart();
	void drawWristPart();
	void drawToolPart();

	GLUquadric *quadric;

	GLuint textures[ROBOTIC_TEXTURES_NO];

	const char* textureNames[ROBOTIC_TEXTURES_NO];
};


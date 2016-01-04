#pragma once

#include "GLUT.H"
#include <iostream>

class Light
{
public:
	~Light();
	Light(const Light& light) = delete;
	void operator= (const Light& light) = delete;
	static Light& getInstance();
	void init();
	void keyboard(unsigned char key, int x, int y);
	void display();

	void setAmbientIntensity(GLfloat _ambientIntensity);
	void setDiffuseIntensity(GLfloat _diffuseIntensity);

	GLfloat getAmbientIntensity();
	GLfloat getDiffuseIntensity();

	void calculateAmbientLight();
	void calculateDiffuseLight();
private:
	Light();

	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;

	GLfloat ambientLightCoeff[4];
	GLfloat diffuseLightCoeff[4];

	GLfloat ambientLight[4];
	GLfloat diffuseLight[4];

	GLfloat matAmbient[4];
	GLfloat matDiffuse[4];
	GLfloat matSpecular[4];
	GLfloat matShininess;

	GLfloat lightPosition[4];

	void(Light::*setVal)(GLfloat);
	GLfloat(Light::*getVal)(void);
	void(Light::*calculate)(void);
};


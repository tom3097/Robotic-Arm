#include "Light.h"


Light::Light() : getVal(nullptr), setVal(nullptr), calculate(nullptr)
{
	matAmbient[0] = 0.329412;
	matAmbient[1] = 0.223529;
	matAmbient[2] = 0.027451;
	matAmbient[3] = 1.00000;

	matDiffuse[0] = 0.780392;
	matDiffuse[1] = 0.568627;
	matDiffuse[2] = 0.113725;
	matDiffuse[3] = 1.000000;

	matSpecular[0] = 0.992157;
	matSpecular[1] = 0.941176;
	matSpecular[2] = 0.807843;
	matSpecular[3] = 1.000000;

	matShininess = 27.8974;

	ambientLightCoeff[0] = 0.05f;
	ambientLightCoeff[1] = 0.05f;
	ambientLightCoeff[2] = 0.05f;
	ambientLightCoeff[3] = 0.05f;

	diffuseLightCoeff[0] = 0.3f;
	diffuseLightCoeff[1] = 0.3f;
	diffuseLightCoeff[2] = 0.3f;
	diffuseLightCoeff[3] = 0.3f;

	lightPosition[0] = 0.0f;
	lightPosition[1] = 500.0f;
	lightPosition[2] = 0.0f;
	lightPosition[3] = 1.0f;

	ambientIntensity = 20;
	diffuseIntensity = 20;
}


Light::~Light()
{
}


Light& Light::getInstance()
{
	static Light light;
	return light;
}


void Light::init()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	calculateAmbientLight();
	calculateDiffuseLight();

	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}


void Light::display()
{
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}


void Light::setAmbientIntensity(GLfloat _ambientIntensity)
{
	ambientIntensity = _ambientIntensity;
	if (ambientIntensity < 0)
		ambientIntensity = 0;
}


void Light::setDiffuseIntensity(GLfloat _diffuseIntensity)
{
	diffuseIntensity = _diffuseIntensity;
	if (diffuseIntensity < 0)
		diffuseIntensity = 0;
}


GLfloat Light::getAmbientIntensity()
{
	return ambientIntensity;
}


GLfloat Light::getDiffuseIntensity()
{
	return diffuseIntensity;
}


void Light::calculateAmbientLight()
{
	ambientLight[0] = ambientLightCoeff[0] * ambientIntensity;
	ambientLight[1] = ambientLightCoeff[1] * ambientIntensity;
	ambientLight[2] = ambientLightCoeff[2] * ambientIntensity;
	ambientLight[3] = ambientLightCoeff[3] * ambientIntensity;

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
}


void Light::calculateDiffuseLight()
{
	diffuseLight[0] = diffuseLightCoeff[0] * diffuseIntensity;
	diffuseLight[1] = diffuseLightCoeff[1] * diffuseIntensity;
	diffuseLight[2] = diffuseLightCoeff[2] * diffuseIntensity;
	diffuseLight[3] = diffuseLightCoeff[3] * diffuseIntensity;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
}


void Light::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '7':
		setVal = &Light::setAmbientIntensity;
		getVal = &Light::getAmbientIntensity;
		calculate = &Light::calculateAmbientLight;
		break;
	case '8':
		setVal = &Light::setDiffuseIntensity;
		getVal = &Light::getDiffuseIntensity;
		calculate = &Light::calculateDiffuseLight;
		break;
	case '9':
		(Light::getInstance().*setVal)((Light::getInstance().*getVal)() + 1);
		(Light::getInstance().*calculate)();
		break;
	case '0':
		(Light::getInstance().*setVal)((Light::getInstance().*getVal)() - 1);
		(Light::getInstance().*calculate)();
		break;
	default:
		break;
	}
}


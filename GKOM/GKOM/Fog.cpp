#include "Fog.h"


Fog::Fog()
{
	mode = GL_EXP;

	density = 0.02f;

	color[0] = 0.87f;
	color[1] = 0.63f;
	color[2] = 0.87f;
	color[3] = 1.0f;

	active = false;
}


Fog::~Fog()
{
}


Fog& Fog::getInstance()
{
	static Fog fog;
	return fog;
}


void Fog::init()
{
	glHint(GL_FOG_HINT, GL_NICEST);

	glFogfv(GL_FOG_COLOR, color);

	glFogf(GL_FOG_DENSITY, density);

	glFogf(GL_FOG_MODE, mode);
}


void Fog::enableDisable()
{
	if (active)
	{
		glDisable(GL_FOG);
		active = false;
	}
	else
	{
		glEnable(GL_FOG);
		active = true;
	}
}


void Fog::changeMode()
{
	if (mode == GL_EXP)
		mode = GL_EXP2;
	else
		mode = GL_EXP;

	glFogi(GL_FOG_MODE, mode);
}


void Fog::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'f':
		enableDisable();
		break;
	case 'b':
		changeMode();
		break;
	case 'n':
		density += 0.005;
		glFogf(GL_FOG_DENSITY, density);
		break;
	case 'm':
		density -= 0.005;
		glFogf(GL_FOG_DENSITY, density);
		break;
	default:
		break;
	}
}
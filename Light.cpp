#include "Light.h"


Light::Light(int name)
{
	this->name = name;
	ambient[0]=1.0;
	ambient[1]=1.0;
	ambient[2]=1.0;
	ambient[3]=1.0;
	diffuse[0]=1.0;
	diffuse[1]=1.0;
	diffuse[2]=1.0;
	diffuse[3]=1.0;
	specular[0]=1.0;
	specular[1]=1.0;
	specular[2]=1.0;
	specular[3]=1.0;
	constAtt = 1.0;
	linAtt = 0.0;
	quadAtt = 0.0;
	initDisplayLists();
}

int Light::getName()
{
	return name;
}

Light::~Light()
{
	glDeleteLists(displayList,1);
}

void Light::translate(double dx, double dy, double dz )
{
	float vals[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef( dx, dy, dz );
	glGetFloatv(GL_MODELVIEW_MATRIX, vals);
	glPopMatrix();
	
	Matrix m(vals);
	//trafoMatrix = m*trafoMatrix;
	translateMatrix = m*translateMatrix;
}


const Matrix& Light::getTransformations() const
{
  	//return trafoMatrix;
	return translateMatrix;
}

void Light::draw(int selectedName)
{
	glPushMatrix();
	//glMultMatrixf( (translateMatrix*rotateMatrix).getValues() );
	glMultMatrixf( translateMatrix.getValues() );
	if (selectedName==name) //set diffuse color if the model is selected (or not)	
		glCallList(greyDisplayList);
	else	
		glCallList(displayList);
	
	glPopMatrix();
}

void Light::initDisplayLists()
{
	displayList = glGenLists(1);
	glNewList(displayList,GL_COMPILE);		
	glDisable(GL_BLEND);		// Turn Blending Off
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular );
	glMaterialf(GL_FRONT, GL_SHININESS, 120.0 );
	GLUquadricObj *quadric1 = gluNewQuadric();
	gluSphere(quadric1, 0.25f, 20, 20);
	glEndList();

	//-------------------------------------------------
	greyDisplayList = glGenLists(1);
	glNewList(greyDisplayList,GL_COMPILE);	
	glDisable(GL_BLEND);		// Turn Blending Off
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient );
	float greydiffuse[] = {0.8,0.8,0.8,1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greydiffuse );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular );
	glMaterialf(GL_FRONT, GL_SHININESS, 120.0 );
	GLUquadricObj *quadric2 = gluNewQuadric();
	gluSphere(quadric2, 0.25f, 20, 20);
	glEndList();
	
}

void Light::setAmbient(float r, float g, float b)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	initDisplayLists();
}

void Light::setDiffuse(float r, float g, float b)
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	initDisplayLists();
}

void Light::setSpecular(float r, float g, float b)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	initDisplayLists();
}

void Light::setAttenuation(float c, float l, float q)
{
	constAtt = c;
	linAtt = l;
	quadAtt = q;
	initDisplayLists();
}

const float* Light::getAmbient () const
{
  	return ambient;  
}

const float* Light::getDiffuse () const
{
  	return diffuse;
}

const float* Light::getSpecular() const
{
  	return specular;
}

const float* Light::getAttenuation () const
{
  	float att[] = {constAtt,linAtt,quadAtt};
	return att;
}





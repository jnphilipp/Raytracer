#ifndef LIGHT_H
#define LIGHT_H

#include "CGMath.h"
#include "Matrix.h"

#include <GL/glu.h>

class Light
{
	public:
		Light(int name);
		~Light();
		
		void translate(double dx, double dy, double dz );

		const Matrix& getTransformations() const;

		void draw(int selectedName);

		int getName();

		void setAmbient(float r, float g, float b);
		void setDiffuse(float r, float g, float b);
		void setSpecular(float r, float g, float b);
		void setAttenuation(float c, float l, float q);

		const float* getAmbient() const;
		const float* getDiffuse() const;
		const float* getSpecular() const;
		const float* getAttenuation() const;


	private:
		Matrix translateMatrix;

		float ambient[4];
		float diffuse[4];
		float specular[4];
		float constAtt;
		float linAtt;
		float quadAtt;

		GLuint displayList;
		GLuint greyDisplayList;

		/*! \brief Name of the primitive, i.e. a consecutive ID. */
        int name;

		void initDisplayLists();
		
		
};

#endif

#ifndef CGMATH_H
#define CGMATH_H

//DataTypes, useful Functions and Math Stuff

#include <vector>
#include <math.h>
#include <string>
#include <QtGui>
#include <QtOpenGL>


class Vector
{
	public:
		Vector()
		{
			values[0] = values[1] = values[2] = 0.0;
  			values[3] = 1.0;
		}

		//this constructor is useful to init texture coords (which are 2D)
		Vector(float x, float y, float z=0, float w=1.0)
		{
			values[0] = x;
			values[1] = y;
			values[2] = z;
			values[3] = w;
		}

		
		float& operator () (size_t i)
		{
			return values[i];
		}

		float operator () (size_t i) const
		{
			return values[i];
		}

		float& operator [] (size_t i)
		{
			return values[i];
		}

		float operator [] (size_t i) const
		{
			return values[i];
		}

		void setValue(int index, float value)
		{
			values[index] = value;
		}

		Vector& operator = ( const Vector& v ) 
		{
			memcpy(values, v.values, 4*sizeof(float));
  			return *this;
		}

		Vector operator + ( const Vector& v ) const
		{
			return Vector( values[0] + v[0], values[1] + v[1], values[2] + v[2] );
		}

		Vector operator - ( const Vector& v ) const
		{
			return Vector( values[0] - v[0], values[1] - v[1], values[2] - v[2] );
		}

		Vector operator - ( ) const
		{
			return Vector( -values[0], -values[1], -values[2]);
		}

		Vector operator * ( const float& scalar ) const
		{
			return Vector( values[0]*scalar, values[1]*scalar, values[2]*scalar );
		}

		Vector operator / ( const float& scalar ) const
		{
			return Vector( values[0]/scalar, values[1]/scalar, values[2]/scalar );
		}

		double normSquare ()
		{
			return values[0]*values[0] + values[1]*values[1] + values[2]*values[2];
		}

		double norm ()
		{
			return sqrt( values[0]*values[0] + values[1]*values[1] + values[2]*values[2] );
		}

		void normalize()
		{
			double n = norm();
			values[0] /= n;
			values[1] /= n;
			values[2] /= n;
		}

		float* getValues ()
		{
			return values;
		}

	private:
		float values[4];
};

inline float scalarProduct( Vector v1, Vector v2 )
{
  	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
};

inline Vector crossProduct( Vector v1, Vector v2 )
{
	return Vector(v1[1]*v2[2] - v2[1]*v1[2], v1[2]*v2[0] - v2[2]*v1[0], v1[0]*v2[1] - v2[0]*v1[1]);
};



struct Texture
{
	unsigned int texID;
	std::string name; //name of the imagefile
	QImage texture;
};


//since this programm works only with triangles every std::vector in the Face-struct has dimension 3
struct Face
{
	std::vector<unsigned int> vectors;
	std::vector<unsigned int> normals;
	std::vector<unsigned int> tex_coords;
};

struct Mesh
{
	std::vector<unsigned int> faces;
	unsigned int material;
};


//--------------esp. for the raytracer-----------------------


struct Lightsource
{
	Vector position;
	float ambient[3];
	float diffuse[3];
	float specular[3];
	float constAtt;
	float linAtt;
	float quadAtt;	
};

struct Material
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
	float alpha; //how much light is goes through an object
	float sharpness; //how is does the material reflect (1.0 -> perfect mirror, 0.0 -> no reflections)
	float density; //index of refraction i.e. how does the light bend when going through an object (1.0 means no bending)
	bool isTexture;
	unsigned int tex_id;
	std::string name;
	QImage texture;
};

struct Triangle //just to have all the informations of Material and 
{
	Material material;
	Vector vertices[3];
	Vector normals[3];
	Vector texCoords[3]; //only [0] and [1] are used to store texInformations
	Vector normal;
	Vector ubeta;
	Vector ugamma;
	float kbeta;
	float kgamma;
};


#endif

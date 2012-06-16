#ifndef CMODEL_H
#define CMODEL_H

#include "Matrix.h"
#include "CGMath.h"
#include <GL/gl.h>
#include <iostream>

using namespace std;

class Model
{
	public:
		/*! \brief Creates model with the given attributes*/
		Model(int name, vector<Vector> vectors, vector<Face> faces, vector<Vector> normals, vector<Mesh> meshes, vector<Material> materials, vector<Vector> tex_coords);
		~Model();
		

		void rotate( Vector axis, float angle );
		void translate(double dx, double dy, double dz );
		void translateTo(double dx, double dy, double dz );
		void scale( double sx, double sy, double sz );
		void transform( const Matrix& matrix );
		Vector getCenter();

		Matrix trafoMatrix;
		Matrix scaleMatrix;
		Matrix rotateMatrix;
		Matrix translateMatrix;

		void draw(int selectedName);

		vector<Mesh> meshes;
		vector<Face> faces;
		vector<Material> materials;
		vector<Vector> normals;
		vector<Vector> vectors;
		vector<Vector> tex_coords;

		/*! \brief Static counter for the names (IDs). 
		//static int nameCount;*/
		
		int getName();


	private:

		GLuint displayList;
		GLuint greyDisplayList;
		Vector center;

		/*! \brief Name of the primitive, i.e. a consecutive ID. */
        	int name;

		void initDisplayLists();
		void calcCenter();
		bool isTransparent(Material material);
		
		
};

#endif


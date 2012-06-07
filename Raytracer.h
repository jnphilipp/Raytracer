#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QtGui>
#include <GL/glew.h>
#include <GL/glext.h>
#include <QtOpenGL>
#include <vector>
#include <cfloat>

#include "CGMath.h"
#include "Octree.h"

#define MAX_DEPTH 4 

class Raytracer : public QGLWidget {
	Q_OBJECT
		public:
			Raytracer( QString file );
			void genImage();

		protected:

			void paintGL();
			void resizeGL( int width, int height );
			void initializeGL();

		private:
			void init();
			bool initShaders();
			void close();
			QColor raytrace(Vector r, Vector e, int depth, Triangle *etriangle, float density);
			void color(Vector p, Vector n, Vector dir, Vector a, Triangle triangle, float a1, float a2, float a3, int depth, float density, float *cr, float *cg, float *cb);

			std::vector<Triangle> triangles; //the triangles in the Scene
			std::vector<Lightsource> lights; //the lights in the scene
			Octree *octree;

			QImage *image;
			QImage finalImage;			
			
			Vector camera, center, upVector;
			QColor backgroundColor, ambientLight;
			
			float focalLength;
			float superSamplingRate;

			//acceleration
			char** renderedImage;
			unsigned int *idx;
			GLuint displayList;
			GLuint screenTexID;
			GLuint fboId;
			
};

#endif

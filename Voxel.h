#ifndef VOXEL_H
#define VOXEL_H

#include <iostream>
#include <algorithm>

//#include "MetaVoxel.h"
#include "CGMath.h"

class Voxel {
	public:
		Voxel(Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz);
		void addTriangle(Triangle *triangle);
		int size();
		bool cutVoxel(Vector *start, Vector *dir);
		Triangle * getTriangle(int i) {
			return triangles[i];
		}

	private:
		Vector minx;
		Vector miny;
		Vector minz;
		Vector maxx;
		Vector maxy;
		Vector maxz;
		//Vector normx;
		//Vector normy;
		//Vector normz;
		std::vector<Triangle *> triangles;
};

#endif

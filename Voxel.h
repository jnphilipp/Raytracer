#ifndef VOXEL_H
#define VOXEL_H

#include <iostream>
#include <algorithm>

#include "CGMath.h"

class Voxel {
	public:
		Voxel(Vector *vldown, Vector *vrtop, Vector *vnormx, Vector *vnormy, Vector *vnormz);
		void addTriangle(Triangle *triangle);
		int size();
		bool cutVoxel(Vector *start, Vector *dir, float dis);
		std::vector<Triangle *> * getTriangles() {
			return &triangles;
		}
		Triangle * getTriangle(int i) {
			return triangles[i];
		}
		Vector * getLdown() {
			return &ldown;
		}
		Vector * getRtop() {
			return &rtop;
		}

	private:
		Vector ldown;
		Vector rtop;
		Vector normx;
		Vector normy;
		Vector normz;
		std::vector<Triangle *> triangles;
};

#endif

#ifndef OCTREE_H
#define OCTREE_H

#include "CGMath.h"
#include "Matrix.h"
#include <vector>
#include <map>
#include <iostream>

//using namespace std;

class Octree {
	private:
		Vector normx;// = Vector(1.0f, 0.0f, 0.0f);
		Vector normy;
		Vector normz;

	public:
		Octree();
		void build(std::vector<Triangle> *triangles, float minx, float miny, float minz, float maxx, float maxy, float maxz);

	private:
	void getVoxelsP(Vector *p, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
	void getVoxelsLx(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
	void getVoxelsLy(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
	void getVoxelsLz(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
	void getVoxelsT(Triangle *triangle, Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
	void getVoxels(float x0, float y0, float z0, std::map<int, int> *voxels);
};

#endif

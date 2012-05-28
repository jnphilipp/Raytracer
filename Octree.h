#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include <map>
#include <iostream>
#include <cfloat>

#include "CGMath.h"
#include "Matrix.h"
#include "Voxel.h"
//#include "SubVoxel.h"

class Octree {
	public:
		Octree();
		void build(std::vector<Triangle> *triangles, float minx, float miny, float minz, float maxx, float maxy, float maxz);
		int size();
		bool cutVoxel(int voxel, Vector *start, Vector *dir);
		float cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *triangle);

	private:
		Vector normx;
		Vector normy;
		Vector normz;
		//SubVoxel *root;
		std::vector<Voxel *> voxels;
		void getVoxelsP(Vector *p, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
		void getVoxelsLx(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
		void getVoxelsLy(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
		void getVoxelsLz(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
		void getVoxelsT(Triangle *triangle, Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels);
		void getVoxels(float x0, float y0, float z0, std::map<int, int> *voxels);
		void buildRec(std::vector<Triangle> *triangles, std::vector<Voxel *> *vox, Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz, Vector middlex, Vector middley, Vector middlez);
};

#endif

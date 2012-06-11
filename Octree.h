#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include <map>
#include <iostream>
#include <cfloat>

#include "CGMath.h"
#include "Matrix.h"
#include "Voxel.h"

#define MAX_TRIANGLES_PER_VOXEL 700
#define MAX_RECURSION_DEPTH 10

class Octree {
	public:
		Octree();
		void build(std::vector<Triangle> *triangles, float minx, float miny, float minz, float maxx, float maxy, float maxz);
		int size();
		bool cutVoxel(int voxel, Vector *start, Vector *dir, float dis);
		float cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *etriangle, Triangle *triangle, Vector *p);
		bool cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *triangle, float dis);
		bool cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *triangle, float dis, float *alpha);

	private:
		Vector normx;
		Vector normy;
		Vector normz;
		std::vector<Voxel *> voxels;

		void getVoxelsP(Vector *p, Vector *middle, std::map<int, int> *voxels);
		void getVoxelsLx(Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels);
		void getVoxelsLy(Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels);
		void getVoxelsLz(Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels);
		void getVoxelsT(Triangle *triangle, Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels);
		void getVoxels(float x0, float y0, float z0, std::map<int, int> *voxels);
		void buildRec(std::vector<Triangle *> *triangles, std::vector<Voxel *> *vox, Vector *ldown, Vector *rtop, int depth);
};

#endif

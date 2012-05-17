#ifndef VOXEL_H
#define VOXEL_H

#include "MetaVoxel.h"

class Voxel : public MetaVoxel {
	public:
		//Voxel(Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz);
		Voxel(Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz);// : MetaVoxel(minx, miny, minz, maxx, maxy, maxz);
		void addTriangle(Triangle *triangle, int voxel);
		int size();

	private:
		/*Vector minx;
		Vector miny;
		Vector minz;
		Vector maxx;
		Vector maxy;
		Vector maxz;*/
		std::vector<Triangle *> triangles;
};

#endif

#ifndef SUBVOXEL_H
#define SUBVOXEL_H

//#include <vector>

#include "MetaVoxel.h"
//#include "CGMath.h"

class SubVoxel : public MetaVoxel {
	public:
		SubVoxel (Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz, Vector *middlex, Vector *middley, Vector *middlez);// : MetaVoxel(minx, miny, minz, maxx, maxy, maxz);
		void addTriangle(Triangle *triangle, int voxel);
		//void addVoxel(MetaVoxel voxel);
		int size() { return -1;}

	private:
		/*Vector minx;
		Vector miny;
		Vector minz;
		Vector maxx;
		Vector maxy;
		Vector maxz;
		std::vector<Triangle *> triangles;*/
		Vector middlex;
		Vector middley;
		Vector middlez;
		MetaVoxel *voxels[8];
};

#endif

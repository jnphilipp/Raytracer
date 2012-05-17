#include "Voxel.h"

/*Voxel::Voxel(Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz) {
	minx = *minx;
	miny = *miny;
	minz = *minz;
	maxx = *maxx;
	maxy = *maxy;
	maxz = *maxz;
}*/

Voxel::Voxel(Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz) : MetaVoxel(minx, miny, minz, maxx, maxy, maxz) {}

void Voxel::addTriangle(Triangle *triangle, int voxel) {
	triangles.push_back(triangle);
}

int Voxel::size() {
	return triangles.size();
}

#include "SubVoxel.h"

SubVoxel::SubVoxel(Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz, Vector *vmiddlex, Vector *vmiddley, Vector *vmiddlez) : MetaVoxel(minx, miny, minz, maxx, maxy, maxz) {
	//voxels[0] = Voxel()
	//voxels = new Voxel[8];
	//voxels[0] = new Voxel();
	middlex = *vmiddlex;
	middley = *vmiddley;
	middlez = *vmiddlez;
}

void SubVoxel::addTriangle(Triangle *triangle, int voxel) {
	/*std::map<int, int> voxels;
	std::map<int, int>::iterator it;

	//first condition
	getVoxelsP(&triangle->vertices[0], &middlex, &middley, &middlez, &voxels);
	getVoxelsP(&triangle->vertices[1], &middlex, &middley, &middlez, &voxels);
	getVoxelsP(&triangle->vertices[2], &middlex, &middley, &middlez, &voxels);

	//second condition
	Vector a = triangle->vertices[1] - triangle->vertices[0];
	Vector b = triangle->vertices[2] - triangle->vertices[0];
	Vector c = triangle->vertices[1] - triangle->vertices[2];

	getVoxelsLx(&triangle->vertices[0], &a, &middlex, &middley, &middlez, &voxels);
	getVoxelsLx(&triangle->vertices[0], &b, &middlex, &middley, &middlez, &voxels);
	getVoxelsLx(&triangle->vertices[2], &c, &middlex, &middley, &middlez, &voxels);
	getVoxelsLy(&triangle->vertices[0], &a, &middlex, &middley, &middlez, &voxels);
	getVoxelsLy(&triangle->vertices[0], &b, &middlex, &middley, &middlez, &voxels);
	getVoxelsLy(&triangle->vertices[2], &c, &middlex, &middley, &middlez, &voxels);
	getVoxelsLz(&triangle->vertices[0], &a, &middlex, &middley, &middlez, &voxels);
	getVoxelsLz(&triangle->vertices[0], &b, &middlex, &middley, &middlez, &voxels);
	getVoxelsLz(&triangle->vertices[2], &c, &middlex, &middley, &middlez, &voxels);

	for ( it = voxels.begin(); it != voxels.end(); it++ ) {
		(*voxels[it->first]).addTriangle(triangle);
	}*/
	(*voxels)[voxel].addTriangle(triangle, voxel);
}

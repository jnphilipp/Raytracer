#include "Voxel.h"

Voxel::Voxel(Vector *vminx, Vector *vminy, Vector *vminz, Vector *vmaxx, Vector *vmaxy, Vector *vmaxz) {
	minx = *vminx;
	miny = *vminy;
	miny = *vminz;
	maxx = *vmaxx;
	maxy = *vmaxy;
	maxz = *vmaxz;
	//normx = Vector(1.0f, 0.0f, 0.0f);
	//normy = Vector(0.0f, 1.0f, 0.0f);
	//normz = Vector(0.0f, 0.0f, 1.0f);
}


void Voxel::addTriangle(Triangle *triangle) {
	triangles.push_back(triangle);
}

int Voxel::size() {
	return triangles.size();
}

bool Voxel::cutVoxel(Vector *start, Vector *dir) {
	Vector ldown = Vector(minx[0], miny[1], minz[2]);std::cout << "ldown: " << ldown[0] << ", " << ldown[1] << ", " << ldown[2] << "\n";
	Vector rtop = Vector(maxx[0], maxy[1], maxz[2]);std::cout << "rtop: " << rtop[0] << ", " << rtop[1] << ", " << rtop[2] << "\n";
	Vector normx = Vector(1.0f, 0.0f, 0.0f);
	Vector normy = Vector(0.0f, 1.0f, 0.0f);
	Vector normz = Vector(0.0f, 0.0f, 1.0f);

	float d, c;
	if ( (d = scalarProduct(*dir, normx)) != 0 ) {
		c = scalarProduct((ldown - *start), normx) / d;

		if ( c < 0 )
			return false;
	}

	if ( (d = scalarProduct(*dir, normy)) != 0 ) {
		c = scalarProduct((ldown - *start), normy) / d;

		if ( c < 0 )
			return false;
	}

	if ( (d = scalarProduct(*dir, normz)) != 0 ) {
		c = scalarProduct((ldown - *start), normz) / d;

		if ( c < 0 )
			return false;
	}

	if ( (d = scalarProduct(*dir, normx)) != 0 ) {
		c = scalarProduct((rtop - *start), normx) / d;

		if ( c < 0 )
			return false;
	}

	if ( (d = scalarProduct(*dir, normy)) != 0 ) {
		c = scalarProduct((rtop - *start), normy) / d;

		if ( c < 0 )
			return false;
	}

	if ( (d = scalarProduct(*dir, normz)) != 0 ) {
		c = scalarProduct((rtop - *start), normz) / d;

		if ( c < 0 )
			return false;
	}

	return true;
}

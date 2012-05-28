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
	std::vector<Triangle *>::iterator it;
	if ( (it = std::find(triangles.begin(), triangles.end(), triangle)) == triangles.end() )
		triangles.push_back(triangle);
}

int Voxel::size() {
	return triangles.size();
}

bool Voxel::cutVoxel(Vector *start, Vector *dir) {
	Vector ldown = Vector(minx[0], miny[1], minz[2]);//std::cout << "ldown: " << ldown[0] << ", " << ldown[1] << ", " << ldown[2] << "\n";
	Vector rtop = Vector(maxx[0], maxy[1], maxz[2]);//std::cout << "rtop: " << rtop[0] << ", " << rtop[1] << ", " << rtop[2] << "\n";
	Vector normx = Vector(1.0f, 0.0f, 0.0f);
	Vector normy = Vector(0.0f, 1.0f, 0.0f);
	Vector normz = Vector(0.0f, 0.0f, 1.0f);

	float d, c;
	if ( (d = scalarProduct(*dir, normx)) != 0 ) {
		c = scalarProduct((ldown - *start), normx) / d;

		Vector p = *start + *dir *c;
		if ( p[0] <= maxx[0] && p[0] >= minx[0] && p[1] <= maxy[1] && p[1] >= miny[1] && p[2] <= maxz[2] && p[2] >= minz[2] ) {
			//std::cout << "p: " << p[0] << ", " << p[1] << ", " << p[2] << "\n";
			return true;
		}
	}
	if ( (d = scalarProduct(*dir, normy)) != 0 ) {
		c = scalarProduct((ldown - *start), normy) / d;

		Vector p = *start + *dir *c;
		if ( p[0] <= maxx[0] && p[0] >= minx[0] && p[1] <= maxy[1] && p[1] >= miny[1] && p[2] <= maxz[2] && p[2] >= minz[2] ) {
			//std::cout << "p: " << p[0] << ", " << p[1] << ", " << p[2] << "\n";
			return true;
		}
	}
	if ( (d = scalarProduct(*dir, normz)) != 0 ) {
		c = scalarProduct((ldown - *start), normz) / d;

		Vector p = *start + *dir *c;
		if ( p[0] <= maxx[0] && p[0] >= minx[0] && p[1] <= maxy[1] && p[1] >= miny[1] && p[2] <= maxz[2] && p[2] >= minz[2] ) {
			//std::cout << "p: " << p[0] << ", " << p[1] << ", " << p[2] << "\n";
			return true;
		}
	}
	if ( (d = scalarProduct(*dir, normx)) != 0 ) {
		c = scalarProduct((rtop - *start), normx) / d;

		Vector p = *start + *dir *c;
		if ( p[0] <= maxx[0] && p[0] >= minx[0] && p[1] <= maxy[1] && p[1] >= miny[1] && p[2] <= maxz[2] && p[2] >= minz[2] ) {
			//std::cout << "p: " << p[0] << ", " << p[1] << ", " << p[2] << "\n";
			return true;
		}
	}
	if ( (d = scalarProduct(*dir, normy)) != 0 ) {
		c = scalarProduct((rtop - *start), normy) / d;

		Vector p = *start + *dir *c;
		if ( p[0] <= maxx[0] && p[0] >= minx[0] && p[1] <= maxy[1] && p[1] >= miny[1] && p[2] <= maxz[2] && p[2] >= minz[2] ) {
			//std::cout << "p: " << p[0] << ", " << p[1] << ", " << p[2] << "\n";
			return true;
		}
	}
	if ( (d = scalarProduct(*dir, normz)) != 0 ) {
		c = scalarProduct((rtop - *start), normz) / d;

		Vector p = *start + *dir *c;
		if ( p[0] <= maxx[0] && p[0] >= minx[0] && p[1] <= maxy[1] && p[1] >= miny[1] && p[2] <= maxz[2] && p[2] >= minz[2] ) {
			//std::cout << "p: " << p[0] << ", " << p[1] << ", " << p[2] << "\n";
			return true;
		}
	}

	return false;
}

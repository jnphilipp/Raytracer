#include "Voxel.h"

Voxel::Voxel(Vector *vldown, Vector *vrtop, Vector *vnormx, Vector *vnormy, Vector *vnormz) {
	ldown = *vldown;
	rtop = *vrtop;
	normx = *vnormx;
	normy = *vnormy;
	normz = *vnormz;
}

/*################################################

Returns the number of triangles the voxel holds.

################################################*/
int Voxel::size() {
	return triangles.size();
}

/*################################################

Adds a triangle to the voxel and makes sure the
triangle wasn't add before.

################################################*/
void Voxel::addTriangle(Triangle *triangle) {
	std::vector<Triangle *>::iterator it;
	if ( (it = std::find(triangles.begin(), triangles.end(), triangle)) == triangles.end() )
		triangles.push_back(triangle);
}

/*################################################

Checks whether a ray intersects this voxels or
not. The variable dis specifies the distance
between the intersection point from the start
point of the ray. In order to ignore the distance
set it to FLT_MAX.

################################################*/
bool Voxel::cutVoxel(Vector *start, Vector *dir, float dis) {
	float d, c;

	//ldown -> x
	if ( (d = dot(*dir, normx)) != 0 ) {
		c = dot((ldown - *start), normx) / d;

		Vector p = *start + *dir * c;
		if ( p[1] <= rtop[1] && p[1] >= ldown[1] && p[2] <= rtop[2] && p[2] >= ldown[2] && (*start - p).norm() <= dis )
			return true;
	}
	//ldown -> y
	if ( (d = dot(*dir, normy)) != 0 ) {
		c = dot((ldown - *start), normy) / d;

		Vector p = *start + *dir * c;
		if ( p[0] <= rtop[0] && p[0] >= ldown[0] && p[2] <= rtop[2] && p[2] >= ldown[2] && (*start - p).norm() <= dis )
			return true;
	}
	//ldown -> z
	if ( (d = dot(*dir, normz)) != 0 ) {
		c = dot((ldown - *start), normz) / d;

		Vector p = *start + *dir * c;
		if ( p[0] <= rtop[0] && p[0] >= ldown[0] && p[1] <= rtop[1] && p[1] >= ldown[1] && (*start - p).norm() <= dis )
			return true;
	}
	//rtop -> x
	if ( (d = dot(*dir, normx)) != 0 ) {
		c = dot((rtop - *start), normx) / d;

		Vector p = *start + *dir * c;
		if ( p[1] <= rtop[1] && p[1] >= ldown[1] && p[2] <= rtop[2] && p[2] >= ldown[2] && (*start - p).norm() <= dis )
			return true;
	}
	//rtop -> y
	if ( (d = dot(*dir, normy)) != 0 ) {
		c = dot((rtop - *start), normy) / d;

		Vector p = *start + *dir * c;
		if ( p[0] <= rtop[0] && p[0] >= ldown[0] && p[2] <= rtop[2] && p[2] >= ldown[2] && (*start - p).norm() <= dis )
			return true;
	}
	//rtop -> z
	if ( (d = dot(*dir, normz)) != 0 ) {
		c = dot((rtop - *start), normz) / d;

		Vector p = *start + *dir * c;
		if ( p[0] <= rtop[0] && p[0] >= ldown[0] && p[1] <= rtop[1] && p[1] >= ldown[1] && (*start - p).norm() <= dis )
			return true;
	}

	return false;
}

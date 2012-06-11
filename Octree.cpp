#include "Octree.h"

Octree::Octree() {
	normx = Vector(1.0f, 0.0f, 0.0f);
	normy = Vector(0.0f, 1.0f, 0.0f);
	normz = Vector(0.0f, 0.0f, 1.0f);
}

/*################################################

Returns the number of voxels this octree holds.

################################################*/
int Octree::size() {
	return voxels.size();
}

/*################################################

Builds the Octree.

################################################*/
void Octree::build(std::vector<Triangle> *triangles, float minx, float miny, float minz, float maxx, float maxy, float maxz) {
	Vector ldown = Vector(minx, miny, minz);
	Vector rtop = Vector(maxx, maxy, maxz);

	if ( triangles->size() > MAX_TRIANGLES_PER_VOXEL ) {
		std::vector<Triangle *> tri;

		for ( unsigned int i = 0; i < triangles->size(); i++ ) {
			tri.push_back(&(*triangles)[i]);
		}

		buildRec(&tri, &voxels, &ldown, &rtop, 0);
	}
	else {
		voxels.push_back(new Voxel(&ldown, &rtop, &normx, &normy, &normz));
		for ( unsigned int i = 0; i < triangles->size(); i++ ) {
			voxels[0]->addTriangle(&((*triangles)[i]));
		}
	}
}

/*################################################

Decides in which voxels the triangles belongs.
If after precessing all triangles a voxel has
more than the maximum number of triangles, the
voxel will build again. The maximum number of
triangles is specified in
MAX_TRIANGLEs_PER_VOXEL.

################################################*/
void Octree::buildRec(std::vector<Triangle *> *triangles, std::vector<Voxel *> *voxels, Vector *ldown, Vector *rtop, int depth) {
	Vector middle = *ldown + (*rtop - *ldown) * 0.5f;
	normx = (Vector((*ldown)[0], middle[1], middle[2]) - middle);
	normy = (Vector(middle[0], (*ldown)[1], middle[2]) - middle);
	normz = (Vector(middle[0], middle[1], (*ldown)[2]) - middle);

	//maximum recusion depth too large
	if ( depth >= MAX_RECURSION_DEPTH ) {
		std::vector<Voxel *> vox;
		vox.push_back(new Voxel(ldown, rtop, &normx, &normy, &normz));

		for ( unsigned int i = 0; i < triangles->size(); i++ )
			vox[0]->addTriangle((*triangles)[i]);
	}

	//create 8 voxels
	std::vector<Voxel *> vox;
	//voxel 0
	vox.push_back(new Voxel(ldown, &middle, &normx, &normy, &normz));
	//voxel 1
	vox.push_back(new Voxel(new Vector(middle[0], (*ldown)[1], (*ldown)[2]), new Vector((*rtop)[0], middle[1], middle[2]), &normx, &normy, &normz));
	//voxel 2
	vox.push_back(new Voxel(new Vector((*ldown)[0], middle[1], (*ldown)[2]), new Vector(middle[0], (*rtop)[1], middle[2]), &normx, &normy, &normz));
	//voxel 3
	vox.push_back(new Voxel(new Vector(middle[0], middle[1], (*ldown)[2]), new Vector((*rtop)[0], (*rtop)[1], middle[2]), &normx, &normy, &normz));
	//voxel 4
	vox.push_back(new Voxel(new Vector((*ldown)[0], (*ldown)[1], middle[2]), new Vector(middle[0], middle[1], (*rtop)[2]), &normx, &normy, &normz));
	//voxel 5
	vox.push_back(new Voxel(new Vector(middle[0], (*ldown)[1], middle[2]), new Vector((*rtop)[0], middle[1], (*rtop)[2]), &normx, &normy, &normz));
	//voxel 6
	vox.push_back(new Voxel(new Vector((*ldown)[0], middle[1], middle[2]), new Vector(middle[0], (*rtop)[1], (*rtop)[2]), &normx, &normy, &normz));
	//voxel 7
	vox.push_back(new Voxel(&middle, rtop, &normx, &normy, &normz));


	for ( unsigned int i = 0; i < triangles->size(); i++ ) {
		std::map<int, int> mvoxels;
		std::map<int, int>::iterator it;

		//corners
		getVoxelsP(&(*triangles)[i]->vertices[0], &middle, &mvoxels);
		getVoxelsP(&(*triangles)[i]->vertices[1], &middle, &mvoxels);
		getVoxelsP(&(*triangles)[i]->vertices[2], &middle, &mvoxels);

		if ( mvoxels.size() > 1 ) {

			Vector a = (*triangles)[i]->vertices[1] - (*triangles)[i]->vertices[0];
			Vector b = (*triangles)[i]->vertices[2] - (*triangles)[i]->vertices[0];
			Vector c = (*triangles)[i]->vertices[1] - (*triangles)[i]->vertices[2];

			//branch lines
			getVoxelsLx(&(*triangles)[i]->vertices[0], &a, &middle, &mvoxels);
			getVoxelsLx(&(*triangles)[i]->vertices[0], &b, &middle, &mvoxels);
			getVoxelsLx(&(*triangles)[i]->vertices[2], &c, &middle, &mvoxels);
			getVoxelsLy(&(*triangles)[i]->vertices[0], &a, &middle, &mvoxels);
			getVoxelsLy(&(*triangles)[i]->vertices[0], &b, &middle, &mvoxels);
			getVoxelsLy(&(*triangles)[i]->vertices[2], &c, &middle, &mvoxels);
			getVoxelsLz(&(*triangles)[i]->vertices[0], &a, &middle, &mvoxels);
			getVoxelsLz(&(*triangles)[i]->vertices[0], &b, &middle, &mvoxels);
			getVoxelsLz(&(*triangles)[i]->vertices[2], &c, &middle, &mvoxels);

			//triangles
			Vector dir = *rtop - *ldown;
			getVoxelsT((*triangles)[i], ldown, &dir, &middle, &mvoxels);

			Vector ld = Vector((*rtop)[0], (*ldown)[1], (*ldown)[2]);
			Vector rt = Vector((*ldown)[0], (*rtop)[1], (*rtop)[2]);
			dir = rt - ld;
			getVoxelsT((*triangles)[i], &ld, &dir, &middle, &mvoxels);

			ld = Vector((*ldown)[0], (*ldown)[1], (*rtop)[2]);
			rt = Vector((*rtop)[0], (*rtop)[1], (*ldown)[2]);
			dir = rt - ld;
			getVoxelsT((*triangles)[i], &ld, &dir, &middle, &mvoxels);

			ld = Vector((*rtop)[0], (*ldown)[1], (*rtop)[2]);
			rt = Vector((*ldown)[0], (*rtop)[1], (*ldown)[2]);
			dir = rt - ld;
			getVoxelsT((*triangles)[i], &ld, &dir, &middle, &mvoxels);
		}

		//triangle -> voxel
		for ( it = mvoxels.begin(); it != mvoxels.end(); it++ )
			vox[it->first]->addTriangle((*triangles)[i]);
	}

	for ( unsigned int i = 0; i < vox.size(); i++ ) {
		if ( vox[i]->size() > MAX_TRIANGLES_PER_VOXEL ) {
			std::vector<Voxel *> tmp;

			buildRec(vox[i]->getTriangles(), &tmp, vox[i]->getLdown(), vox[i]->getRtop(), depth++);

			for ( unsigned int j = 0; j < tmp.size(); j++ )
				voxels->push_back(tmp[j]);
		}
		else {
			if ( vox[i]->size() != 0 )
				voxels->push_back(vox[i]);
		}
	}
}

/*################################################

Checks if the specified voxel is intersected. The
variable dis specifies the distance between the
intersection point from the start point of the
ray. In order to ignore the distance set it to
FLT_MAX.

################################################*/
bool Octree::cutVoxel(int voxel, Vector *start, Vector *dir, float dis) {
	return voxels[voxel]->cutVoxel(start, dir, dis);
}

/*################################################

Checks which triangle of the specified voxel is
intersected and have dis minimum distance to
the start point of the ray. The intersected
triangle and the distance will be returned.

################################################*/
float Octree::cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *etriangle, Triangle *triangle, Vector *p) {
	float dis = FLT_MAX;

	for ( int i = 0; i < voxels[voxel]->size(); i++ ) {
		if ( etriangle != NULL && (*etriangle) == (*voxels[voxel]->getTriangle(i)) )
			continue;

		Vector q;
		if ( cut(start, dir, voxels[voxel]->getTriangle(i), &q) ) {
			float tmp = (*start - q).norm();
			if ( tmp < dis ) {
				dis = tmp;
				*triangle = *(voxels[voxel]->getTriangle(i));
				*p = q;
			}
		}
	}

	return dis;
}

/*################################################

Checks whether a triangle intersects with the ray
in the given distance.

################################################*/
bool Octree::cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *triangle, float dis) {
	for ( int i = 0; i < voxels[voxel]->size(); i++ ) {
		if ( (*triangle) == (*voxels[voxel]->getTriangle(i)) )
			continue;

		float t;
		if ( cut(start, dir, voxels[voxel]->getTriangle(i), &t) ) {
			if ( t >= 0 && t <= dis )
				return true;
		}
	}

	return false;
}


/*################################################
################################################*/
bool Octree::cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *triangle, float dis, float *alpha) {
	for ( int i = 0; i < voxels[voxel]->size(); i++ ) {
		if ( (*triangle) == (*voxels[voxel]->getTriangle(i)) )
			continue;

		float t;
		if ( cut(start, dir, voxels[voxel]->getTriangle(i), &t) ) {
			if ( t >= 0 && t <= dis ) {
				if ( *alpha == 0.0f )
					return true;
				else
					*alpha -= voxels[voxel]->getTriangle(i)->material.alpha;
			}
		}
	}

	if ( *alpha > 0.0f && *alpha <= 1.0f )
		return false;
	else
		return true;
}


/*################################################

Checks in which voxels the point lies. The map
holds the results.

################################################*/
void Octree::getVoxelsP(Vector *p, Vector *middle, std::map<int, int> *voxels) {
	float x0 =  dot((*p - *middle), normx);
	float y0 =  dot((*p - *middle), normy);
	float z0 =  dot((*p - *middle), normz);

	getVoxels(x0, y0, z0, voxels);
}

/*################################################

Checks in which voxels the intersection point of
the ray and the x-plane lies. The map holds the
results.

################################################*/
void Octree::getVoxelsLx(Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels) {
	float d;
	if ( (d = dot(*dir, normx)) != 0 ) {
		float x0 = dot((*middle - *start), normx) / d;

		if ( x0 <= 0 || x0 >= 1 )
			return;

		Vector p = *start + *dir * x0;

		float y0 =  dot((p - *middle), normy);
		float z0 =  dot((p - *middle), normz);

		getVoxels(x0, y0, z0, voxels);
	}
}

/*################################################

Checks in which voxels the intersection point of
the ray and the y-plane lies. The map holds the
results.

################################################*/
void Octree::getVoxelsLy(Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels) {
	float d;
	if ( (d = dot(*dir, normy)) != 0 ) {
		float y0 = dot((*middle - *start), normy) / d;

		if ( y0 <= 0 || y0 >= 1 )
			return;

		Vector p = *start + *dir * y0;

		float x0 =  dot((p - *middle), normx);
		float z0 =  dot((p - *middle), normz);

		getVoxels(x0, y0, z0, voxels);
	}
}

/*################################################

Checks in which voxels the intersection point of
the ray and the z-plane lies. The map holds the
results.

################################################*/
void Octree::getVoxelsLz(Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels) {
	float d;
	if ( (d = dot(*dir, normz)) != 0 ) {
		float z0 = dot((*middle - *start), normz) / d;

		if ( z0 <= 0 || z0 >= 1 )
			return;

		Vector p = *start + *dir * z0;

		float x0 =  dot((p - *middle), normx);
		float y0 =  dot((p - *middle), normy);

		getVoxels(x0, y0, z0, voxels);
	}
}

/*################################################

Checks in which voxels the intersection point of
the triangle and the ray lies. The map holds the
results.

################################################*/
void Octree::getVoxelsT(Triangle *triangle, Vector *start, Vector *dir, Vector *middle, std::map<int, int> *voxels) {
	Vector p;
	if ( cut(start, dir, triangle, &p) )
		getVoxelsP(&p, middle, voxels);
}

/*################################################

Checks in which voxels the 'point' belongs,
depending on the sign. The map holds the results.


   +-- ––––– ---
   /|        /|
  / |       / |
+-+ ––––– --+ |
 |  |      |  |
 |  |      |  |
 | ++- ––––– -+-
 | /       | /
 |/        |/
+++ ––––– -++

################################################*/
void Octree::getVoxels(float x0, float y0, float z0, std::map<int, int> *voxels) {
	if ( x0 >= 0 && y0 >= 0 && z0 >= 0 )
		(*voxels)[0] = 0;
	if ( x0 <= 0 && y0 >= 0 && z0 >= 0 )
		(*voxels)[1] = 1;
	if ( x0 >= 0 && y0 <= 0 && z0 >= 0 )
		(*voxels)[2] = 2;
	if ( x0 <= 0 && y0 <= 0 && z0 >= 0 )
		(*voxels)[3] = 3;
	if ( x0 >= 0 && y0 >= 0 && z0 <= 0 )
		(*voxels)[4] = 4;
	if ( x0 <= 0 && y0 >= 0 && z0 <= 0 )
		(*voxels)[5] = 5;
	if ( x0 >= 0 && y0 <= 0 && z0 <= 0 )
		(*voxels)[6] = 6;
	if ( x0 <= 0 && y0 <= 0 && z0 <= 0 )
		(*voxels)[7] = 7;
}

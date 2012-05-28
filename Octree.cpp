#include "Octree.h"

Octree::Octree() {
	normx = Vector(1.0f, 0.0f, 0.0f);
	normy = Vector(0.0f, 1.0f, 0.0f);
	normz = Vector(0.0f, 0.0f, 1.0f);
}

int Octree::size() {
	return voxels.size();
}

void Octree::build(std::vector<Triangle> *triangles, float minx, float miny, float minz, float maxx, float maxy, float maxz) {
	Vector vminx = Vector(minx, 0.0f, 0.0f);
	Vector vmaxx = Vector(maxx, 0.0f, 0.0f);
	Vector vminy = Vector(0.0f, miny, 0.0f);
	Vector vmaxy = Vector(0.0f, maxy, 0.0f);
	Vector vminz = Vector(0.0f, 0.0f, minz);
	Vector vmaxz = Vector(0.0f, 0.0f, maxz);
	Vector middlex = Vector((minx + maxx)/2.0f, 0.0f, 0.0f);
	Vector middley = Vector(0.0f, (miny + maxy)/2.0f, 0.0f);
	Vector middlez = Vector(0.0f, 0.0f, (minz + maxz)/2.0f);

	std::cout << "maxy: " << maxy << "\n";
	std::cout << "miny: " << miny << "\n";

	//Voxel vox[8];
	std::vector<Voxel *> vox;
	//for ( int i = 0; i < 8; i++ )
	buildRec(triangles, &vox, &vminx, &vminy, &vminz, &vmaxx, &vmaxy, &vmaxz, middlex, middley, middlez);
	for ( int i = 0; i < 8; i++ )
		std::cout << i << ": " << vox[i]->size() << "\n";

	voxels = vox;
}

void Octree::buildRec(std::vector<Triangle> *triangles, std::vector<Voxel *> *vox, Vector *minx, Vector *miny, Vector *minz, Vector *maxx, Vector *maxy, Vector *maxz, Vector middlex, Vector middley, Vector middlez) {
	std::cout << "middlex: (" << middlex[0] << ", " << middlex[1] << ", " << middlex[2] << ")\n";
	std::cout << "middley: (" << middley[0] << ", " << middley[1] << ", " << middley[2] << ")\n";
	std::cout << "middlez: (" << middlez[0] << ", " << middlez[1] << ", " << middlez[2] << ")\n\n";
	(*vox).push_back(new Voxel(minx, miny, minz, &middlex, &middley, &middlez));
	(*vox).push_back(new Voxel(&middlex, miny, minz, maxx, &middley, &middlez));
	(*vox).push_back(new Voxel(minx, &middley, minz, &middlex, maxy, &middlez));
	(*vox).push_back(new Voxel(&middlex, &middley, minz, maxx, maxy, &middlez));
	(*vox).push_back(new Voxel(minx, miny, &middlez, &middlex, &middley, maxz));
	(*vox).push_back(new Voxel(&middlex, miny, &middlez, maxx, &middley, maxz));
	(*vox).push_back(new Voxel(minx, &middley, &middlez, &middlex, maxy, maxz));
	(*vox).push_back(new Voxel(&middlex, &middley, &middlez, maxx, maxy, maxz));
	/*std::cout << "minx: " << minx << "\n";
	std::cout << "maxx: " << maxy << "\n";
	std::cout << "miny: " << miny << "\n";
	std::cout << "maxy: " << maxy << "\n";
	std::cout << "minz: " << minz << "\n";
	std::cout << "maxz: " << maxz << "\n";*/

	//miny
	Vector v1 = (crossProduct(normy, normz) * (scalarProduct(*minx, normx)) - (crossProduct(normx, normz) * scalarProduct(*miny, normy)) + (crossProduct(normx, normy) * scalarProduct(*minz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v2 = (crossProduct(normy, normz) * (scalarProduct(*maxx, normx)) - (crossProduct(normx, normz) * scalarProduct(*miny, normy)) + (crossProduct(normx, normy) * scalarProduct(*minz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v3 = (crossProduct(normy, normz) * (scalarProduct(*maxx, normx)) - (crossProduct(normx, normz) * scalarProduct(*miny, normy)) + (crossProduct(normx, normy) * scalarProduct(*maxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v4 = (crossProduct(normy, normz) * (scalarProduct(*minx, normx)) - (crossProduct(normx, normz) * scalarProduct(*miny, normy)) + (crossProduct(normx, normy) * scalarProduct(*maxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();

	//miny - maxy
	Vector v16 = (crossProduct(normy, normz) * (scalarProduct(middlex, normx)) - (crossProduct(normx, normz) * scalarProduct(middley, normy)) + (crossProduct(normx, normy) * scalarProduct(middlez, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();


	//maxy
	Vector v19 = (crossProduct(normy, normz) * (scalarProduct(*minx, normx)) - (crossProduct(normx, normz) * scalarProduct(*maxy, normy)) + (crossProduct(normx, normy) * scalarProduct(*minz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v20 = (crossProduct(normy, normz) * (scalarProduct(*maxx, normx)) - (crossProduct(normx, normz) * scalarProduct(*maxy, normy)) + (crossProduct(normx, normy) * scalarProduct(*minz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v21 = (crossProduct(normy, normz) * (scalarProduct(*maxx, normx)) - (crossProduct(normx, normz) * scalarProduct(*maxy, normy)) + (crossProduct(normx, normy) * scalarProduct(*maxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v22 = (crossProduct(normy, normz) * (scalarProduct(*minx, normx)) - (crossProduct(normx, normz) * scalarProduct(*maxy, normy)) + (crossProduct(normx, normy) * scalarProduct(*maxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();


	/*std::cout << "x: " << v1.getValues()[0] << "\ty: " << v1.getValues()[1] << "\tz: " << v1.getValues()[2] << "\n";
	std::cout << "x: " << v2.getValues()[0] << "\ty: " << v2.getValues()[1] << "\tz: " << v2.getValues()[2] << "\n";
	std::cout << "x: " << v3.getValues()[0] << "\ty: " << v3.getValues()[1] << "\tz: " << v3.getValues()[2] << "\n";
	std::cout << "x: " << v4.getValues()[0] << "\ty: " << v4.getValues()[1] << "\tz: " << v4.getValues()[2] << "\n";
	std::cout << "\n";
	std::cout << "x: " << v16.getValues()[0] << "\ty: " << v16.getValues()[1] << "\tz: " << v16.getValues()[2] << "\n";
	std::cout << "\n";
	std::cout << "x: " << v19.getValues()[0] << "\ty: " << v19.getValues()[1] << "\tz: " << v19.getValues()[2] << "\n";
	std::cout << "x: " << v20.getValues()[0] << "\ty: " << v20.getValues()[1] << "\tz: " << v20.getValues()[2] << "\n";
	std::cout << "x: " << v21.getValues()[0] << "\ty: " << v21.getValues()[1] << "\tz: " << v21.getValues()[2] << "\n";
	std::cout << "x: " << v22.getValues()[0] << "\ty: " << v22.getValues()[1] << "\tz: " << v22.getValues()[2] << "\n";*/

	/*std::map<int, int> vp;
	std::map<int, int>::iterator it;
	getVoxelsP(&v1, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v1: " << it->first << "\n";
	vp.clear();

	getVoxelsP(&v2, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v2: " << it->first << "\n";
	vp.clear();

	getVoxelsP(&v3, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v3: " << it->first << "\n";
	vp.clear();

	getVoxelsP(&v4, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v4: " << it->first << "\n";
	vp.clear();

	getVoxelsP(&v19, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v19: " << it->first << "\n";
	vp.clear();

	getVoxelsP(&v20, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v20: " << it->first << "\n";
	vp.clear();

	getVoxelsP(&v21, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v21: " << it->first << "\n";
	vp.clear();

	getVoxelsP(&v22, &middlex, &middley, &middlez, &vp);
	for ( it = vp.begin(); it != vp.end(); it++ )
		std::cout << "v22: " << it->first << "\n";*/


	for ( int i = 0; i < triangles->size(); i++ ) {
		std::map<int, int> mvoxels;
		std::map<int, int>::iterator it;

		getVoxelsP(&(*triangles)[i].vertices[0], &middlex, &middley, &middlez, &mvoxels);
		getVoxelsP(&(*triangles)[i].vertices[1], &middlex, &middley, &middlez, &mvoxels);
		getVoxelsP(&(*triangles)[i].vertices[2], &middlex, &middley, &middlez, &mvoxels);

		//std::cout << "1. voxels: " << mvoxels.size() << "\n";
		if ( mvoxels.size() > 1 ) {

			Vector a = (*triangles)[i].vertices[1] - (*triangles)[i].vertices[0];
			Vector b = (*triangles)[i].vertices[2] - (*triangles)[i].vertices[0];
			Vector c = (*triangles)[i].vertices[1] - (*triangles)[i].vertices[2];

			/*getVoxelsLx(&(*triangles)[i].vertices[0], &a, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLx(&(*triangles)[i].vertices[0], &b, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLx(&(*triangles)[i].vertices[2], &c, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLy(&(*triangles)[i].vertices[0], &a, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLy(&(*triangles)[i].vertices[0], &b, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLy(&(*triangles)[i].vertices[2], &c, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLz(&(*triangles)[i].vertices[0], &a, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLz(&(*triangles)[i].vertices[0], &b, &middlex, &middley, &middlez, &mvoxels);
			getVoxelsLz(&(*triangles)[i].vertices[2], &c, &middlex, &middley, &middlez, &mvoxels);


			//std::cout << "2. voxels: " << mvoxels.size() << "\n";

			Vector dir = v16 - v1;
			getVoxelsT(&((*triangles)[i]), &v1, &dir, &middlex, &middley, &middlez, &mvoxels);

			dir = v16 - v2;
			getVoxelsT(&((*triangles)[i]), &v2, &dir, &middlex, &middley, &middlez, &mvoxels);

			dir = v16 - v3;
			getVoxelsT(&((*triangles)[i]), &v3, &dir, &middlex, &middley, &middlez, &mvoxels);

			dir = v16 - v4;
			getVoxelsT(&((*triangles)[i]), &v4, &dir, &middlex, &middley, &middlez, &mvoxels);

			dir = v16 - v19;
			getVoxelsT(&((*triangles)[i]), &v19, &dir, &middlex, &middley, &middlez, &mvoxels);

			dir = v16 - v20;
			getVoxelsT(&((*triangles)[i]), &v20, &dir, &middlex, &middley, &middlez, &mvoxels);

			dir = v16 - v21;
			getVoxelsT(&((*triangles)[i]), &v21, &dir, &middlex, &middley, &middlez, &mvoxels);

			dir = v16 - v22;
			getVoxelsT(&((*triangles)[i]), &v22, &dir, &middlex, &middley, &middlez, &mvoxels);*/

			//std::cout << "3. voxels: " << mvoxels.size() << "\n";
		}

		for ( it = mvoxels.begin(); it != mvoxels.end(); it++ ) {
			(*vox)[it->first]->addTriangle(&((*triangles)[i]));
			//std::cout << it->first << ": " << (*vox)[it->first]->size() << "\n";
		}//std::cout << "\n";
		if ( mvoxels.size() == 0 )
			std::cout << "null\n";

		/*std::cout << "\n\n";
		if ( i == 0 || i == 1 )
			std::cout << "triangle " << i << ": " << (*triangles)[i].vertices[0].getValues()[0] << ", " << (*triangles)[i].vertices[0].getValues()[1] << ", " << (*triangles)[i].vertices[0].getValues()[2] << "\n";*/
		//std::cout << "\n\n";
	}
}

bool Octree::cutVoxel(int voxel, Vector *start, Vector *dir) {
	//std::cout << "cut voxel: " << voxel << "|" << voxels.size() << "\n";
	return voxels[voxel]->cutVoxel(start, dir);
}

float Octree::cutTriangles(int voxel, Vector *start, Vector *dir, Triangle *triangle) {
	float dis = FLT_MAX;
	//std::cout << "cut triangle: " << voxel << "(voxel)\n";
	for ( int i = 0; i < voxels[voxel]->size(); i++ ) {
		Vector p;
		if ( cut(start, dir, voxels[voxel]->getTriangle(i), &p) ) {
			float tmp = (*start - p).norm();
			if ( tmp < dis ) {
				dis = tmp;
				triangle = voxels[voxel]->getTriangle(i);
			}
		}
	}

	return dis;
}

void Octree::getVoxelsP(Vector *p, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
	float x0 =  scalarProduct((*p - *x), normx);
	float y0 =  scalarProduct((*p - *y), normy);
	float z0 =  scalarProduct((*p - *z), normz);
	//std::cout << "x0: " << x0 << "\ty0: " << y0 << "\tz0: " << z0 << "\n";
	getVoxels(x0, y0, z0, voxels);
}

void Octree::getVoxelsLx(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
	float d;
	if ( (d = scalarProduct(*dir, normx)) != 0 ) {
		float x0 = scalarProduct((*x - *start), normx) / d;

		if ( x0 <= 0 || x0 >= 1 )
			return;

		Vector p = *start + *dir * x0;

		float y0 =  scalarProduct((p - *y), normy);
		float z0 =  scalarProduct((p - *z), normz);

		getVoxels(x0, y0, z0, voxels);
	}
}

void Octree::getVoxelsLy(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
	float d;
	if ( (d = scalarProduct(*dir, normy)) != 0 ) {
		float y0 = scalarProduct((*y - *start), normy) / d;

		if ( y0 <= 0 || y0 >= 1 )
			return;

		Vector p = *start + *dir * y0;

		float x0 =  scalarProduct((p - *x), normx);
		float z0 =  scalarProduct((p - *z), normz);

		getVoxels(x0, y0, z0, voxels);
	}
}

void Octree::getVoxelsLz(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
	float d;
	if ( (d = scalarProduct(*dir, normz)) != 0 ) {
		float z0 = scalarProduct((*z - *start), normz) / d;

		if ( z0 <= 0 || z0 >= 1 )
			return;

		Vector p = *start + *dir * z0;

		float x0 =  scalarProduct((p - *x), normx);
		float y0 =  scalarProduct((p - *y), normy);

		getVoxels(x0, y0, z0, voxels);
	}
}

void Octree::getVoxelsT(Triangle *triangle, Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
//		if ( (d = scalarProduct(v16 - v1, (*triangles)[i].normal)) != 0  ) {
	Vector p;
	if ( cut(start, dir, triangle, &p) )
		getVoxelsP(&p, x, y, z, voxels);
}

void Octree::getVoxels(float x0, float y0, float z0, std::map<int, int> *voxels) {
	if ( x0 <= 0 && y0 <= 0 && z0 <= 0 )
		(*voxels)[0] = 0;
	if ( x0 >= 0 && y0 <= 0 && z0 <= 0 )
		(*voxels)[1] = 1;
	if ( x0 <= 0 && y0 >= 0 && z0 <= 0 )
		(*voxels)[2] = 2;
	if ( x0 >= 0 && y0 >= 0 && z0 <= 0 )
		(*voxels)[3] = 3;
	if ( x0 <= 0 && y0 <= 0 && z0 >= 0 )
		(*voxels)[4] = 4;
	if ( x0 >= 0 && y0 <= 0 && z0 >= 0 )
		(*voxels)[5] = 5;
	if ( x0 <= 0 && y0 >= 0 && z0 >= 0 )
		(*voxels)[6] = 6;
	if ( x0 >= 0 && y0 >= 0 && z0 >= 0 )
		(*voxels)[7] = 7;
}

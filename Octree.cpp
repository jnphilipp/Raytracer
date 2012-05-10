#include "Octree.h"

//using namespace std;

Octree::Octree() {
	normx = Vector(1.0f, 0.0f, 0.0f);
	normy = Vector(0.0f, 1.0f, 0.0f);
	normz = Vector(0.0f, 0.0f, 1.0f);
}

void Octree::build(std::vector<Triangle> *triangles, float minx, float miny, float minz, float maxx, float maxy, float maxz) {
	Vector vminx = Vector(minx, 0.0f, 0.0f);
	Vector vmaxx = Vector(maxx, 0.0f, 0.0f);
	Vector vminy = Vector(0.0f, miny, 0.0f);
	Vector vmaxy = Vector(0.0f, maxy, 0.0f);
	Vector vminz = Vector(0.0f, 0.0f, minz);
	Vector vmaxz = Vector(0.0f, 0.0f, maxz);
	Vector middelx = Vector(minx + (maxx - minx)/2, 0.0f, 0.0f);
	Vector middely = Vector(0.0f, miny + (maxy - miny)/2, 0.0f);
	Vector middelz = Vector(0.0f, 0.0f, minz + (maxz - minz)/2);
	std::cout << "minx: " << minx << "\n";
	std::cout << "maxx: " << maxy << "\n";
	std::cout << "miny: " << miny << "\n";
	std::cout << "maxy: " << maxy << "\n";
	std::cout << "minz: " << minz << "\n";
	std::cout << "maxz: " << maxz << "\n";
	//std::cout << "middely: " << middely.getValues()[1] << "\n";

	//p = (dot(p1,n1)*cross(n2,n3)-dot(p2,n2)*cross(n1,n3)+dot(p3,n3)*cross(n1,n2))/d 
	//miny
	Vector v1 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v2 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v3 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v4 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
/*	Vector v5 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v6 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v7 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v8 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v9 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(vminy, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();*/


	//miny - maxy
	/*Vector v10 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v11 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v12 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v13 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v14 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v15 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();*/
	Vector v16 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
/*	Vector v17 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v18 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(middely, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();*/


	//maxy
	Vector v19 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v20 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v21 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v22 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
/*	Vector v23 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(vminz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v24 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(vmaxz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v25 = (crossProduct(normy, normz) * (scalarProduct(middelx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v26 = (crossProduct(normy, normz) * (scalarProduct(vminx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();
	Vector v27 = (crossProduct(normy, normz) * (scalarProduct(vmaxx, normx)) - (crossProduct(normx, normz) * scalarProduct(vmaxy, normy)) + (crossProduct(normx, normy) * scalarProduct(middelz, normz))) / Matrix(&normx, &normy, &normz).Determinant4f();*/


	std::cout << "x: " << v1.getValues()[0] << "\ty: " << v1.getValues()[1] << "\tz: " << v1.getValues()[2] << "\n";
	std::cout << "x: " << v2.getValues()[0] << "\ty: " << v2.getValues()[1] << "\tz: " << v2.getValues()[2] << "\n";
	std::cout << "x: " << v3.getValues()[0] << "\ty: " << v3.getValues()[1] << "\tz: " << v3.getValues()[2] << "\n";
	std::cout << "x: " << v4.getValues()[0] << "\ty: " << v4.getValues()[1] << "\tz: " << v4.getValues()[2] << "\n";
	/*std::cout << "x: " << v5.getValues()[0] << "\ty: " << v5.getValues()[1] << "\tz: " << v5.getValues()[2] << "\n";
	std::cout << "x: " << v6.getValues()[0] << "\ty: " << v6.getValues()[1] << "\tz: " << v6.getValues()[2] << "\n";
	std::cout << "x: " << v7.getValues()[0] << "\ty: " << v7.getValues()[1] << "\tz: " << v7.getValues()[2] << "\n";
	std::cout << "x: " << v8.getValues()[0] << "\ty: " << v8.getValues()[1] << "\tz: " << v8.getValues()[2] << "\n";
	std::cout << "x: " << v9.getValues()[0] << "\ty: " << v9.getValues()[1] << "\tz: " << v9.getValues()[2] << "\n";*/
	std::cout << "\n";
	/*std::cout << "x: " << v10.getValues()[0] << "\ty: " << v10.getValues()[1] << "\tz: " << v10.getValues()[2] << "\n";
	std::cout << "x: " << v11.getValues()[0] << "\ty: " << v11.getValues()[1] << "\tz: " << v11.getValues()[2] << "\n";
	std::cout << "x: " << v12.getValues()[0] << "\ty: " << v12.getValues()[1] << "\tz: " << v12.getValues()[2] << "\n";
	std::cout << "x: " << v13.getValues()[0] << "\ty: " << v13.getValues()[1] << "\tz: " << v13.getValues()[2] << "\n";
	std::cout << "x: " << v14.getValues()[0] << "\ty: " << v14.getValues()[1] << "\tz: " << v14.getValues()[2] << "\n";
	std::cout << "x: " << v15.getValues()[0] << "\ty: " << v15.getValues()[1] << "\tz: " << v15.getValues()[2] << "\n";*/
	std::cout << "x: " << v16.getValues()[0] << "\ty: " << v16.getValues()[1] << "\tz: " << v16.getValues()[2] << "\n";
	/*std::cout << "x: " << v17.getValues()[0] << "\ty: " << v17.getValues()[1] << "\tz: " << v17.getValues()[2] << "\n";
	std::cout << "x: " << v18.getValues()[0] << "\ty: " << v18.getValues()[1] << "\tz: " << v18.getValues()[2] << "\n";*/
	std::cout << "\n";
	std::cout << "x: " << v19.getValues()[0] << "\ty: " << v19.getValues()[1] << "\tz: " << v19.getValues()[2] << "\n";
	std::cout << "x: " << v20.getValues()[0] << "\ty: " << v20.getValues()[1] << "\tz: " << v20.getValues()[2] << "\n";
	std::cout << "x: " << v21.getValues()[0] << "\ty: " << v21.getValues()[1] << "\tz: " << v21.getValues()[2] << "\n";
	std::cout << "x: " << v22.getValues()[0] << "\ty: " << v22.getValues()[1] << "\tz: " << v22.getValues()[2] << "\n";
	/*std::cout << "x: " << v23.getValues()[0] << "\ty: " << v23.getValues()[1] << "\tz: " << v23.getValues()[2] << "\n";
	std::cout << "x: " << v24.getValues()[0] << "\ty: " << v24.getValues()[1] << "\tz: " << v24.getValues()[2] << "\n";
	std::cout << "x: " << v25.getValues()[0] << "\ty: " << v25.getValues()[1] << "\tz: " << v25.getValues()[2] << "\n";
	std::cout << "x: " << v26.getValues()[0] << "\ty: " << v26.getValues()[1] << "\tz: " << v26.getValues()[2] << "\n";
	std::cout << "x: " << v27.getValues()[0] << "\ty: " << v27.getValues()[1] << "\tz: " << v27.getValues()[2] << "\n";*/

	for ( int i = 0; i < triangles->size(); i++ ) {
		std::map<int, int> voxels;
		//std::cout << "1: " << scalarProduct(((*triangles)[i].vertices[0] - middely), normy) << "\n";
		//std::cout << "2: " << scalarProduct(((*triangles)[i].vertices[1] - middely), normy) << "\n";
		//std::cout << "3: " << scalarProduct(((*triangles)[i].vertices[2] - middely), normy) << "\n";

		/*float x0 =  scalarProduct(((*triangles)[i].vertices[0] - middelx), normx);
		float y0 =  scalarProduct(((*triangles)[i].vertices[0] - middely), normy);
		float z0 =  scalarProduct(((*triangles)[i].vertices[0] - middelz), normz);*/

		getVoxelsP(&(*triangles)[i].vertices[0], &middelx, &middely, &middelz, &voxels);
		getVoxelsP(&(*triangles)[i].vertices[1], &middelx, &middely, &middelz, &voxels);
		getVoxelsP(&(*triangles)[i].vertices[2], &middelx, &middely, &middelz, &voxels);
		
		/*float x1 =  scalarProduct(((*triangles)[i].vertices[1] - middelx), normx);
		float y1 =  scalarProduct(((*triangles)[i].vertices[1] - middely), normy);
		float z1 =  scalarProduct(((*triangles)[i].vertices[1] - middelz), normz);
		
		float x2 =  scalarProduct(((*triangles)[i].vertices[2] - middelx), normx);
		float y2 =  scalarProduct(((*triangles)[i].vertices[2] - middely), normy);
		float z2 =  scalarProduct(((*triangles)[i].vertices[2] - middelz), normz);*/


		/*if ( x0 <= 0 && y0 <= 0 && z0 <= 0 )
			voxels[0] = 0;
		if ( x0 <= 0 && y0 <= 0 && z0 >= 0 )
			voxels[1] = 1;
		if ( x0 <= 0 && y0 >= 0 && z0 <= 0 )
			voxels[2] = 2;
		if ( x0 >= 0 && y0 <= 0 && z0 <= 0 )
			voxels[3] = 3;
		if ( x0 >= 0 && y0 <= 0 && z0 >= 0 )
			voxels[4] = 4;
		if ( x0 >= 0 && y0 >= 0 && z0 <= 0 )
			voxels[5] = 5;
		if ( x0 >= 0 && y0 >= 0 && z0 >= 0 )
			voxels[6] = 6;
		if ( x0 <= 0 && y0 >= 0 && z0 >= 0 )
			voxels[7] = 7;*/


		/*if ( x1 <= 0 && y1 <= 0 && z1 <= 0 )
			voxels[0] = 0;
		if ( x1 <= 0 && y1 <= 0 && z1 >= 0 )
			voxels[1] = 1;
		if ( x1 <= 0 && y1 >= 0 && z1 <= 0 )
			voxels[2] = 2;
		if ( x1 >= 0 && y1 <= 0 && z1 <= 0 )
			voxels[3] = 3;
		if ( x1 >= 0 && y1 <= 0 && z1 >= 0 )
			voxels[4] = 4;
		if ( x1 >= 0 && y1 >= 0 && z1 <= 0 )
			voxels[5] = 5;
		if ( x1 >= 0 && y1 >= 0 && z1 >= 0 )
			voxels[6] = 6;
		if ( x1 <= 0 && y1 >= 0 && z1 >= 0 )
			voxels[7] = 7;


		if ( x2 <= 0 && y2 <= 0 && z2 <= 0 )
			voxels[0] = 0;
		if ( x2 <= 0 && y2 <= 0 && z2 >= 0 )
			voxels[1] = 1;
		if ( x2 <= 0 && y2 >= 0 && z2 <= 0 )
			voxels[2] = 2;
		if ( x2 >= 0 && y2 <= 0 && z2 <= 0 )
			voxels[3] = 3;
		if ( x2 >= 0 && y2 <= 0 && z2 >= 0 )
			voxels[4] = 4;
		if ( x2 >= 0 && y2 >= 0 && z2 <= 0 )
			voxels[5] = 5;
		if ( x2 >= 0 && y2 >= 0 && z2 >= 0 )
			voxels[6] = 6;
		if ( x2 <= 0 && y2 >= 0 && z2 >= 0 )
			voxels[7] = 7;*/

		std::cout << "1. voxels: " << voxels.size() << "\n";
		if ( voxels.size() != 1 ) {

		Vector a = (*triangles)[i].vertices[1] - (*triangles)[i].vertices[0];
		Vector b = (*triangles)[i].vertices[2] - (*triangles)[i].vertices[0];
		Vector c = (*triangles)[i].vertices[1] - (*triangles)[i].vertices[2];
		//float d = 0.0f;


//float x0 =  scalarProduct(((*triangles)[i].vertices[0] - middelx), normx);
//float y0 =  scalarProduct(((*triangles)[i].vertices[0] - middely), normy);
//float z0 =  scalarProduct(((*triangles)[i].vertices[0] - middelz), normz);



//getVoxelsL(Vector *start, Vector *dir, Vector *p1, Vector *norm1, Vector *p2, Vector *norm2, Vector *p3, Vector *norm3, map<int, int> *voxels)
		getVoxelsLx(&(*triangles)[i].vertices[0], &a, &middelx, &middely, &middelz, &voxels);
		getVoxelsLx(&(*triangles)[i].vertices[0], &b, &middelx, &middely, &middelz, &voxels);
		getVoxelsLx(&(*triangles)[i].vertices[2], &c, &middelx, &middely, &middelz, &voxels);
		getVoxelsLy(&(*triangles)[i].vertices[0], &a, &middelx, &middely, &middelz, &voxels);
		getVoxelsLy(&(*triangles)[i].vertices[0], &b, &middelx, &middely, &middelz, &voxels);
		getVoxelsLy(&(*triangles)[i].vertices[2], &c, &middelx, &middely, &middelz, &voxels);
		getVoxelsLz(&(*triangles)[i].vertices[0], &a, &middelx, &middely, &middelz, &voxels);
		getVoxelsLz(&(*triangles)[i].vertices[0], &b, &middelx, &middely, &middelz, &voxels);
		getVoxelsLz(&(*triangles)[i].vertices[2], &c, &middelx, &middely, &middelz, &voxels);


std::cout << "2. voxels: " << voxels.size() << "\n";
/*map<int, int>::iterator it;
for ( it = voxels.begin(); it != voxels.end(); it++ )
	cout << it->first << " ";
cout << "\n";

		for ( int j = 0; j < 9; j++ ) {
			switch ( j ) {
				case 0: {
					if ( (d = scalarProduct(a, normx)) != 0 ) {
						x0 = scalarProduct((middelx - (*triangles)[i].vertices[0]), normx) / d;

						Vector p = (*triangles)[i].vertices[0] + a * x0;

						y0 =  scalarProduct((p - middely), normy);
						z0 =  scalarProduct((p - middelz), normz);
					}
					else
						continue;
				} break;
				case 1: {
					if ( (d = scalarProduct(b, normx)) != 0 ) {
						x0 = scalarProduct((middelx - (*triangles)[i].vertices[0]), normx) / d;

						Vector p = (*triangles)[i].vertices[0] + b * x0;

						y0 =  scalarProduct((p - middely), normy);
						z0 =  scalarProduct((p - middelz), normz);
				}
				else
					continue;
				} break;
				case 2: {
					if ( (d = scalarProduct(c, normx)) != 0 ) {
						x0 = scalarProduct((middelx - (*triangles)[i].vertices[2]), normx) / d;

						Vector p = (*triangles)[i].vertices[2] + c * x0;

						y0 =  scalarProduct((p - middely), normy);
						z0 =  scalarProduct((p - middelz), normz);
					}
					else
						continue;
				} break;
				case 3: {
					if ( (d = scalarProduct(a, normy)) != 0 ) {
						y0 = scalarProduct((middely - (*triangles)[i].vertices[0]), normy) / d;

						Vector p = (*triangles)[i].vertices[0] + a * y0;

						x0 =  scalarProduct((p - middelx), normx);
						z0 =  scalarProduct((p - middelz), normz);
					}
					else
						continue;
				} break;
				case 4: {
					if ( (d = scalarProduct(b, normy)) != 0 ) {
						y0 = scalarProduct((middely - (*triangles)[i].vertices[0]), normy) / d;

						Vector p = (*triangles)[i].vertices[0] + b * y0;

						x0 =  scalarProduct((p - middelx), normx);
						z0 =  scalarProduct((p - middelz), normz);
					}
					else
						continue;
				} break;
				case 5: {
					if ( (d = scalarProduct(c, normy)) != 0 ) {
						y0 = scalarProduct((middely - (*triangles)[i].vertices[2]), normy) / d;

						Vector p = (*triangles)[i].vertices[2] + c * y0;

						x0 =  scalarProduct((p - middelx), normx);
						z0 =  scalarProduct((p - middelz), normz);
					}
					else
						continue;
				} break;
				case 6: {
					if ( (d = scalarProduct(a, normz)) != 0 ) {
						z0 = scalarProduct((middelz - (*triangles)[i].vertices[0]), normz) / d;

						Vector p = (*triangles)[i].vertices[0] + a * z0;

						x0 =  scalarProduct((p - middelx), normx);
						y0 =  scalarProduct((p - middely), normy);
					}
					else
						continue;
				} break;
				case 7: {
					if ( (d = scalarProduct(b, normz)) != 0 ) {
						z0 = scalarProduct((middelz - (*triangles)[i].vertices[0]), normz) / d;

						Vector p = (*triangles)[i].vertices[0] + b * z0;

						x0 =  scalarProduct((p - middelx), normx);
						y0 =  scalarProduct((p - middelz), normy);
					}
					else
						continue;
				} break;
				case 8: {
					if ( (d = scalarProduct(c, normz)) != 0 ) {
						z0 = scalarProduct((middelz - (*triangles)[i].vertices[2]), normz) / d;

						Vector p = (*triangles)[i].vertices[2] + c * z0;

						x0 =  scalarProduct((p - middelx), normx);
						y0 =  scalarProduct((p - middely), normy);
					}
					else
						continue;
				} break;
			}


			if ( x0 <= 0 && y0 <= 0 && z0 <= 0 )
				cout << "Voxel 0: " << i << "\n";
			if ( x0 <= 0 && y0 <= 0 && z0 >= 0 )
				cout << "Voxel 1: " << i << "\n";
			if ( x0 <= 0 && y0 >= 0 && z0 <= 0 )
				cout << "Voxel 2: " << i << "\n";
			if ( x0 >= 0 && y0 <= 0 && z0 <= 0 )
				cout << "Voxel 3: " << i << "\n";
			if ( x0 >= 0 && y0 <= 0 && z0 >= 0 )
				cout << "Voxel 4: " << i << "\n";
			if ( x0 >= 0 && y0 >= 0 && z0 <= 0 )
				cout << "Voxel 5: " << i << "\n";
			if ( x0 >= 0 && y0 >= 0 && z0 >= 0 )
				cout << "Voxel 6: " << i << "\n";
			if ( x0 <= 0 && y0 >= 0 && z0 >= 0 )
				cout << "Voxel 7: " << i << "\n";
		}

		std::cout << "2_. voxels: " << voxels.size() << "\n";*/

		Vector dir = v16 - v1;
		getVoxelsT(&((*triangles)[i]), &v1, &dir, &middelx, &middely, &middelz, &voxels);

		dir = v16 - v2;
		getVoxelsT(&((*triangles)[i]), &v2, &dir, &middelx, &middely, &middelz, &voxels);

		dir = v16 - v3;
		getVoxelsT(&((*triangles)[i]), &v3, &dir, &middelx, &middely, &middelz, &voxels);

		dir = v16 - v4;
		getVoxelsT(&((*triangles)[i]), &v4, &dir, &middelx, &middely, &middelz, &voxels);

		dir = v16 - v19;
		getVoxelsT(&((*triangles)[i]), &v19, &dir, &middelx, &middely, &middelz, &voxels);

		dir = v16 - v20;
		getVoxelsT(&((*triangles)[i]), &v20, &dir, &middelx, &middely, &middelz, &voxels);

		dir = v16 - v21;
		getVoxelsT(&((*triangles)[i]), &v21, &dir, &middelx, &middely, &middelz, &voxels);

		dir = v16 - v22;
		getVoxelsT(&((*triangles)[i]), &v22, &dir, &middelx, &middely, &middelz, &voxels);

		/*if ( (d = scalarProduct(v16 - v1, (*triangles)[i].normal)) != 0  ) {
			Vector p;
			Vector dir = v16 - v1;
			bool c = cut(&v1, &dir, &((*triangles)[i]), &p);
			//std::cout << "v1-t: " << t << "\n";
			if ( c ) {
				std::cout << "cut: (" << p[0] << ", " << p[1] << ", " << p[2] << ")\n";
				getVoxelsP(&p, &middelx, &middely, &middelz, &voxels);
				std::cout << "voxels: " << voxels.size() << "\n";
			}
		}
		if ( (d = scalarProduct(v16 - v2, (*triangles)[i].normal)) != 0  ) {
			float t = scalarProduct(((*triangles)[i].vertices[0] - v2), (*triangles)[i].normal) / d;
			if ( t >= 0 && t <= 1 ) {
				std::cout << "v2-t: " << t << "\n";
			}
		}
		if ( (d = scalarProduct(v16 - v3, (*triangles)[i].normal)) != 0  ) {
			float t = scalarProduct(((*triangles)[i].vertices[0] - v3), (*triangles)[i].normal) / d;
			if ( t >= 0 && t <= 1 ) {
				std::cout << "v3-t: " << t << "\n";
			}
		}
		if ( (d = scalarProduct(v16 - v4, (*triangles)[i].normal)) != 0  ) {
			float t = scalarProduct(((*triangles)[i].vertices[0] - v4), (*triangles)[i].normal) / d;
			if ( t >= 0 && t <= 1 ) {
				std::cout << "v4-t: " << t << "\n";
			}
		}
		if ( (d = scalarProduct(v16 - v19, (*triangles)[i].normal)) != 0  ) {
			float t = scalarProduct(((*triangles)[i].vertices[0] - v19), (*triangles)[i].normal) / d;
			if ( t >= 0 && t <= 1 ) {
				std::cout << "v19-t: " << t << "\n";
			}
		}
		if ( (d = scalarProduct(v16 - v20, (*triangles)[i].normal)) != 0  ) {
			float t = scalarProduct(((*triangles)[i].vertices[0] - v20), (*triangles)[i].normal) / d;
			if ( t >= 0 && t <= 1 ) {
				std::cout << "v20-t: " << t << "\n";
			}
		}
		if ( (d = scalarProduct(v16 - v21, (*triangles)[i].normal)) != 0  ) {
			float t = scalarProduct(((*triangles)[i].vertices[0] - v21), (*triangles)[i].normal) / d;
			if ( t >= 0 && t <= 1 ) {
				std::cout << "v21-t: " << t << "\n";
			}
		}
		if ( (d = scalarProduct(v16 - v22, (*triangles)[i].normal)) != 0  ) {
			float t = scalarProduct(((*triangles)[i].vertices[0] - v22), (*triangles)[i].normal) / d;
			if ( t >= 0 && t <= 1 ) {
				std::cout << "v22-t: " << t << "\n";
			}
		}*/

		std::cout << "3. voxels: " << voxels.size() << "\n";
}
		/*std::cout << "\n\n";
		if ( i == 0 || i == 1 )
			std::cout << "triangle " << i << ": " << (*triangles)[i].vertices[0].getValues()[0] << ", " << (*triangles)[i].vertices[0].getValues()[1] << ", " << (*triangles)[i].vertices[0].getValues()[2] << "\n";*/
		std::cout << "\n\n";
	}

/*	Vector m =  v1 + (v16-v1) * 1 ;
	Vector m1 =  v1 + (v16-v1) * 0 ;
	Vector n =  v2 + (v16-v2) * 1 ;
	Vector n1 =  v2 + (v16-v2) * 0 ;
	std::cout << "m: " << m.getValues()[0] << ", " << m.getValues()[1] << ", " << m.getValues()[2] << "\n";
	std::cout << "n: " << n.getValues()[0] << ", " << n.getValues()[1] << ", " << n.getValues()[2] << "\n";
	std::cout << "v16: " << v16.getValues()[0] << ", " << v16.getValues()[1] << ", " << v16.getValues()[2] << "\n";
	std::cout << "m1: " << m1.getValues()[0] << ", " << m1.getValues()[1] << ", " << m1.getValues()[2] << "\n";
	std::cout << "n1: " << n1.getValues()[0] << ", " << n1.getValues()[1] << ", " << n1.getValues()[2] << "\n";
	std::cout << "v1: " << v1.getValues()[0] << ", " << v1.getValues()[1] << ", " << v1.getValues()[2] << "\n";
	std::cout << "v2: " << v2.getValues()[0] << ", " << v2.getValues()[1] << ", " << v2.getValues()[2] << "\n";*/
}

void Octree::getVoxelsP(Vector *p, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
	float x0 =  scalarProduct(((*p) - (*x)), (normx));
	float y0 =  scalarProduct(((*p) - (*y)), (normy));
	float z0 =  scalarProduct(((*p) - (*z)), (normz));

	getVoxels(x0, y0, z0, voxels);
}

void Octree::getVoxelsLx(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
	float d;
	if ( (d = scalarProduct(*dir, normx)) != 0 ) {
		float x0 = scalarProduct((*x - *start), normx) / d;

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

		Vector p = *start + *dir * z0;

		float x0 =  scalarProduct((p - *x), normx);
		float y0 =  scalarProduct((p - *y), normy);

		getVoxels(x0, y0, z0, voxels);
	}
}

void Octree::getVoxelsT(Triangle *triangle, Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
//		if ( (d = scalarProduct(v16 - v1, (*triangles)[i].normal)) != 0  ) {
	Vector p;
	bool c = cut(start, dir, triangle, &p);

	if ( c )
		getVoxelsP(&p, x, y, z, voxels);
}

void Octree::getVoxels(float x0, float y0, float z0, std::map<int, int> *voxels) {
	if ( x0 <= 0 && y0 <= 0 && z0 <= 0 )
		(*voxels)[0] = 0;
	if ( x0 <= 0 && y0 <= 0 && z0 >= 0 )
		(*voxels)[1] = 1;
	if ( x0 <= 0 && y0 >= 0 && z0 <= 0 )
		(*voxels)[2] = 2;
	if ( x0 >= 0 && y0 <= 0 && z0 <= 0 )
		(*voxels)[3] = 3;
	if ( x0 >= 0 && y0 <= 0 && z0 >= 0 )
		(*voxels)[4] = 4;
	if ( x0 >= 0 && y0 >= 0 && z0 <= 0 )
		(*voxels)[5] = 5;
	if ( x0 >= 0 && y0 >= 0 && z0 >= 0 )
		(*voxels)[6] = 6;
	if ( x0 <= 0 && y0 >= 0 && z0 >= 0 )
		(*voxels)[7] = 7;
}

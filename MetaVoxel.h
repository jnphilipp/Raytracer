#ifndef METAVOXEL_H
#define METAVOXEL_H

#include <vector>

#include "CGMath.h"

class MetaVoxel {
	public:
		MetaVoxel(Vector *vminx, Vector *vminy, Vector *vminz, Vector *vmaxx, Vector *vmaxy, Vector *vmaxz) {
			minx = *vminx;
			miny = *vminy;
			miny = *vminz;
			maxx = *vmaxx;
			maxy = *vmaxy;
			maxz = *vmaxz;
			normx = Vector(1.0f, 0.0f, 0.0f);
			normy = Vector(0.0f, 1.0f, 0.0f);
			normz = Vector(0.0f, 0.0f, 1.0f);
		}
		virtual void addTriangle(Triangle *triangle, int voxel) = 0;
		virtual int size() = 0;

	private:
		Vector minx;
		Vector miny;
		Vector minz;
		Vector maxx;
		Vector maxy;
		Vector maxz;
		Vector normx;
		Vector normy;
		Vector normz;

	protected:
		void getVoxelsP(Vector *p, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
			float x0 =  scalarProduct(((*p) - (*x)), (normx));
			float y0 =  scalarProduct(((*p) - (*y)), (normy));
			float z0 =  scalarProduct(((*p) - (*z)), (normz));

			getVoxels(x0, y0, z0, voxels);
		}
		void getVoxelsLx(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
			float d;
			if ( (d = scalarProduct(*dir, normx)) != 0 ) {
				float x0 = scalarProduct((*x - *start), normx) / d;

				if ( x0 < 0 || x0 > 1 )
					return;

				Vector p = *start + *dir * x0;

				float y0 =  scalarProduct((p - *y), normy);
				float z0 =  scalarProduct((p - *z), normz);

				getVoxels(x0, y0, z0, voxels);
			}
		}
		void getVoxelsLy(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
			float d;
			if ( (d = scalarProduct(*dir, normy)) != 0 ) {
				float y0 = scalarProduct((*y - *start), normy) / d;

				if ( y0 < 0 || y0 > 1 )
					return;

				Vector p = *start + *dir * y0;

				float x0 =  scalarProduct((p - *x), normx);
				float z0 =  scalarProduct((p - *z), normz);

				getVoxels(x0, y0, z0, voxels);
			}
		}
		void getVoxelsLz(Vector *start, Vector *dir, Vector *x, Vector *y, Vector *z, std::map<int, int> *voxels) {
			float d;
			if ( (d = scalarProduct(*dir, normz)) != 0 ) {
				float z0 = scalarProduct((*z - *start), normz) / d;

				if ( z0 < 0 || z0 > 1 )
					return;

				Vector p = *start + *dir * z0;

				float x0 =  scalarProduct((p - *x), normx);
				float y0 =  scalarProduct((p - *y), normy);

				getVoxels(x0, y0, z0, voxels);
			}
		}
		void getVoxels(float x0, float y0, float z0, std::map<int, int> *voxels) {
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
		//std::vector<Triangle *> triangles;
};

#endif

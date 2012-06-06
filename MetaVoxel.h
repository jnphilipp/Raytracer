#ifndef METAVOXEL_H
#define METAVOXEL_H

#include <vector>

#include "CGMath.h"

class MetaVoxel {
	public:
		MetaVoxel(Vector *ldown, Vector *rtop, Vector *normx, Vector *normy, Vector *normz) {
			ldown = *ldwon;
			rtop = *rtop;
			normx = *normx;
			normy = *normy;
			normz = *normz;
		}
		//virtual void addTriangle(Triangle *triangle) = 0;
		virtual int size() = 0;

	private:
		Vector ldown;
		Vector rtop;
		Vector normx;
		Vector normy;
		Vector normz;
};

#endif

#include "Grid.h"

int Grid::getWidth(){ return width; }
int Grid::getHeight(){ return height; }

Grid::Grid(int w, int h):width(w),height(h){}

ConstantGrid::ConstantGrid(int w, int h, int val):Grid(w,h),val(val){}

int ConstantGrid::sample(int w, int h){
	return val;
}

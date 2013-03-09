#include "Grid.h"

int Grid::getWidth(){ return width; }
int Grid::getHeight(){ return height; }

Grid::Grid(int w, int h):width(w),height(h){}

/*
 * ConstantGrid
 */
ConstantGrid::ConstantGrid(int w, int h, int val):Grid(w,h),val(val){}

int ConstantGrid::sample(int x, int y){
	return val;
}

/*
 * CheckerGrid
 */
CheckerGrid::CheckerGrid(int w, int h, int val1, int val2)
:Grid(w,h),val1(val1),val2(val2){};

int CheckerGrid::sample(int x, int y){
	return (x + y) % 2 == 0 ? val1 : val2 ;
}

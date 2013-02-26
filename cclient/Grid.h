#ifndef _GRID_H
#define _GRID_H

class Grid {
public:
	int getHeight();
	int getWidth();

	Grid(int w, int h);

	virtual int sample(int x, int y) = 0;

private:
	int width;
	int height;
};

//Some simple grids for testing

class ConstantGrid : public Grid {
public:
	ConstantGrid(int w, int h, int val);

	int sample(int x, int y);

private:
	int val;
};

class CheckerGrid : public Grid {
public:
	CheckerGrid(int w, int h, int val1, int val2);

	int sample(int x, int y);

private:
	int val1;
	int val2;
};


#endif

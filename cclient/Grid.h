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

class ConstantGrid : public Grid {
public:
	ConstantGrid(int w, int h, int val);

	int sample(int x, int y);

private:
	int val;
};


#endif
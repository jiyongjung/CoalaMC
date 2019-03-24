#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")

#include <math.h>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

void locateBlockIfAir(BlockID block, int x, int y, int z, bool emptyOnly)
{
	if (!emptyOnly || getBlockType(x, y, z) == BLOCK_AIR) {

		locateBlock(block, x, y, z);
	}
}


void drawLine(BlockID block, int x1, int y1, int z1, int x2, int y2, int z2, bool emptyOnly)
{
	int dx = abs(x2 - x1), sx = (x1 < x2) ? 1 : -1;
	int dz = abs(z2 - z1), sz = (z1 < z2) ? 1 : -1;

	locateBlockIfAir(block, x1, y1, z1, emptyOnly);
	for (int err = (dx > dz ? dx : -dz) / 2; x1 != x2 || z1 != z2; ) {
		int e2 = err;

		if (e2 > -dx) { err -= dz; x1 += sx; }
		if (e2 < dz) { err += dx; z1 += sz; }

		locateBlockIfAir(block, x1, y1, z1, emptyOnly);
	}
}

void drawForward(BlockID block, int count, bool emptyOnly)
{

	int px, py, pz;
	getPlayerLocation(&px, &py, &pz);

	double dir = getPlayerDirection();

	double radian = dir * M_PI / 180.;

	int dx = -count * sin(radian);
	int dz = count * cos(radian);
	int ex = count * sin(M_PI / 2 - radian);
	int ez = count * cos(M_PI / 2 - radian);
	int fx = dx + ex;
	int fz = dz + ez;
	int i;
	for (i = 0; i < 11; i++) {
		drawLine(block, px, py + i, pz, px + dx, py + i, pz + dz, emptyOnly);
		drawLine(block, px, py + i, pz, px + ex, py + i, pz + ez, emptyOnly);
		drawLine(block, px + dx, py + i, pz + dz, px + fx, py + i, pz + fz, emptyOnly);
		drawLine(block, px + ex, py + i, pz + ez, px + fx, py + i, pz + fz, emptyOnly);
	}
	drawLine(block, px, py + 10, pz, px + fx, py + 10, pz + fz, emptyOnly);
	drawLine(block, px + ex, py + 10, pz + ez, px + dx, py + 10, pz + dz, emptyOnly);




}

int main()
{
	BlockID diamond = createBlock(BLOCK_DIAMOND);
	drawForward(diamond, 10, true);

}

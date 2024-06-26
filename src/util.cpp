#include "common.h"
using namespace std;
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) and (max(y1, y2) < min(y1 + h1, y2 + h2));
}
void aim(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
    int space = max(abs(x1 - x2), abs(y1 - y2));
    if (space == 0)
    {
        *dx = *dy = 0;
        return;
    }
    *dx = (x1 - x2);*dx /= space;*dy = (y1 - y2);*dy /= space;
}
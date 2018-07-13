
#include "polyinterp.h"

int interpolate_linear ( const struct point2d* p, struct point2d* pt )
{
	pt->y = ((p[1].x - pt->x) * p[0].y + (pt->x - p[0].x) * p[1].y) / (p[1].x - p[0].x);
	return 0;
}

int interpolate_linear_line ( struct interp1d* line, const struct point2d* p)
{
	line->m = (p[1].y - p[0].y) / ( p[1].x - p[0].x );
	line->x0 = p[0].x;
	line->y0 = p[0].y;

	return 0;
}

int interpolate_linear_calc ( const struct interp1d* line, struct point2d* pt)
{
	pt->y = line->y0 + line->m * (pt->x - line->x0);
	
	return 0;
}


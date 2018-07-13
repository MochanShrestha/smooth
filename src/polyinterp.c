
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

int interpolate_quadratic ( const struct point2d* p, struct point2d* q )
{
    // Use the quadratic Lagrange formula to calculate the value at point q.x
    double x = q->x;
    double L0 = (x - p[1].x)*(x - p[2].x)/( (p[0].x - p[1].x) * (p[0].x - p[2].x) );
    double L1 = (x - p[0].x)*(x - p[2].x)/((p[1].x - p[0].x)*(p[1].x - p[2].x));
    double L2 = (x - p[0].x)*(x - p[1].x)/((p[2].x - p[0].x)*(p[2].x - p[1].x));

    double y = p[0].y*L0 + p[1].y*L1 + p[2].y*L2;
    q->y = y;

    return 0;
}

int interpolate_poly ( const struct point2d* p, int n, struct point2d* q ) {
    // Use Lagrange formula to calculate the value at point q.x
    double x = q->x;

    // Lagrange multipliers
    double L[n];
    for (int i=0; i<n; i++) {
        L[i] = 1.0;
        for (int j=0; j<n; j++) {
            if (i!=j) {
                L[i] *= (x - p[j].x);
                L[i] /= (p[i].x - p[j].x);
            }
        }
    }

    // Calculate value of y
    double y = 0.0;
    for (int i=0; i<n; i++) {
        y += p[i].y * L[i];
    }

    q->y = y;

    return 0;
}

#ifndef _POLYINTERP_H_
#define _POLYINTERP_H_

// point in 2d space
struct point2d {
	double x, y;
};

// Given the pts p1 and p2, find the linear interpolated value at p.x
int interpolate_linear ( const struct point2d* p, struct point2d* pt );

// result of 1d interpolation
struct interp1d {
	double m;	// slope
	double x0, y0;	// first point
};

// Calculate the interpolation equation from the given points
int interpolate_linear_line ( struct interp1d* line, const struct point2d* p);

// Calculated the interpolated line from the interpolation data
int interpolate_linear_calc ( const struct interp1d* line, struct point2d* pt);

#endif


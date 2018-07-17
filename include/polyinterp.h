
#ifndef _POLYINTERP_H_
#define _POLYINTERP_H_

// point in 2d space
struct point2d {
    double x, y;
};

struct points2d {
    int n;          // Number of points
    double *x, *y;  // array of x and y co-ordinates
};

// Given two points in p, find the linear interpolated value at pt.x
int interpolate_linear ( const struct point2d* p, struct point2d* pt );

// result of 1d interpolation
struct interp1d {
    double m;	// slope
    double b;   // intercept
};

// Calculate the interpolation equation from the given points
int interpolate_linear_line ( struct interp1d* line, const struct point2d* p);

// Calculated the interpolated line from the interpolation data
int interpolate_linear_calc ( const struct interp1d* line, struct point2d* pt);


// Given 3 points in p, find the linear interpolated values at p.x
int interpolate_quadratic ( const struct point2d* p, struct point2d* q );


// Given n points, interpolate using a n-1 degree polynomial and evaluate at the point q
int interpolate_poly ( const struct point2d* p, int n, struct point2d* q );

// Given n points, interpolate using a n-1 degree polynomial and evaluate at point q.x 
// using Neville's method 
int interpolate_poly_neville(const struct point2d* p, int n, struct point2d* q);

// Given n points, interpolate using a n-1 degree polynomial and evaluate at point q.x
// using Newton's method
int interpolate_poly_newton(const struct points2d* p, struct point2d* q);

#endif



#include "gtest/gtest.h"

extern "C" {
#include "polyinterp.h"
}

// Do linear interpolation between the points (1,1) and (4,2) and evaluate
// the value at x=2
TEST( PolyInterp, LinearInterpolation ) {
	struct point2d p[3];
	
	p[0].x = 1; p[0].y = 1;
	p[1].x = 4; p[1].y = 2;
	p[2].x = 2;

	interpolate_linear ( p, p+2 );

	ASSERT_EQ(4.0/3.0, p[2].y);

	struct interp1d line;

	interpolate_linear_line (&line, p);
	
	ASSERT_EQ(1.0/3.0, line.m);

	struct point2d pt;
	pt.x = 2;
	interpolate_linear_calc (&line, &pt);

	ASSERT_EQ(4.0/3.0, pt.y);
}

// Do quadratic interpolation between the points (-1,2), (0,1) and (1,2) and evaluate
// the value at x=2
TEST ( PolyInterp, QuadraticInterpolation ) {
    struct point2d p[3], q;

    p[0].x = -1; p[0].y = 2;
    p[1].x = 0;  p[1].y = 1;
    p[2].x = 1;  p[2].y = 2;
    q.x = 2;

    interpolate_quadratic(p, &q);

    ASSERT_EQ(5.0, q.y);
}

TEST ( PolyInterp, NthDegreeInterpolation ) {
    struct point2d p[3], q;

    p[0].x = -1; p[0].y = 2;
    p[1].x = 0;  p[1].y = 1;
    p[2].x = 1;  p[2].y = 2;
    q.x = 2;

    interpolate_poly(p, 2, &q);

    ASSERT_EQ(-1.0, q.y);

    interpolate_poly(p, 3, &q);

    ASSERT_EQ(5.0, q.y);
}
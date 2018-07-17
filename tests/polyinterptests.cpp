
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

    ASSERT_DOUBLE_EQ(4.0/3.0, p[2].y);

    struct interp1d line;

    interpolate_linear_line (&line, p);

    ASSERT_DOUBLE_EQ(1.0/3.0, line.m);

    struct point2d pt;
    pt.x = 2;
    interpolate_linear_calc (&line, &pt);

    ASSERT_DOUBLE_EQ(4.0/3.0, pt.y);
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

    ASSERT_DOUBLE_EQ(5.0, q.y);
}

TEST ( PolyInterp, NthDegreeInterpolation ) {
    struct point2d p[3], q;

    p[0].x = -1; p[0].y = 2;
    p[1].x = 0;  p[1].y = 1;
    p[2].x = 1;  p[2].y = 2;
    q.x = 2;

    interpolate_poly(p, 2, &q);

    ASSERT_DOUBLE_EQ(-1.0, q.y);

    interpolate_poly(p, 3, &q);

    ASSERT_DOUBLE_EQ(5.0, q.y);
}

TEST(PolyInterp, NthDegreeNeville) {
    struct point2d p[3], q;

    p[0].x = -1; p[0].y = 2;
    p[1].x = 0;  p[1].y = 1;
    p[2].x = 1;  p[2].y = 2;
    q.x = 2;

    interpolate_poly_neville(p, 2, &q);

    ASSERT_DOUBLE_EQ(-1.0, q.y);

    interpolate_poly_neville(p, 3, &q);

    ASSERT_DOUBLE_EQ(5.0, q.y);

    p[0].x = 0;  p[0].y = 1;
    p[1].x = 1;  p[1].y = 3;
    p[2].x = 3;  p[2].y = 2;
    q.x = 2;

    interpolate_poly_neville(p, 3, &q);

    ASSERT_DOUBLE_EQ(10.0/3.0, q.y);
}

TEST(PolyInterp, NthDegreeLagrangeVsNeville) {
    struct point2d p[6], q1, q2;

    p[0].x = -1;  p[0].y = 1;
    p[1].x = 0;   p[1].y = 4;
    p[2].x = 1.5; p[1].y = 3;
    p[3].x = 2;   p[1].y = -1;
    p[4].x = 3;   p[1].y = 6;
    p[5].x = 4.5; p[1].y = 1;

    q1.x = 1; q2.x = 1;
    interpolate_poly(p, 6, &q1);
    interpolate_poly_neville(p, 6, &q2);

    ASSERT_DOUBLE_EQ(q1.y, q2.y);

    q1.x = 2; q2.x = 2;
    interpolate_poly(p, 6, &q1);
    interpolate_poly_neville(p, 6, &q2);

    ASSERT_DOUBLE_EQ(q1.y, q2.y);
}

TEST(PolyInterp, NthDegreeNewtons) {
    struct points2d p;
    struct point2d q;
    double x[3], y[3];
    p.x = x;
    p.y = y;

    x[0] = -1; y[0] = 2;
    x[1] = 0;  y[1] = 1;
    x[2] = 1;  y[2] = 2;
    q.x = 2;

    p.n = 2;
    interpolate_poly_newton(&p, &q);

    ASSERT_DOUBLE_EQ(-1.0, q.y);

    p.n = 3;
    interpolate_poly_newton(&p, &q);

    ASSERT_DOUBLE_EQ(5.0, q.y);

    x[0] = 0;  y[0] = 1;
    x[1] = 1;  y[1] = 3;
    x[2] = 3;  y[2] = 2;
    q.x = 2;

    p.n = 3;
    interpolate_poly_newton(&p, &q);

    ASSERT_DOUBLE_EQ(10.0/3.0, q.y);
}
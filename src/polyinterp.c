
#include <stdlib.h>
#include <memory.h>

#include "polyinterp.h"

int interpolate_linear ( const struct point2d* p, struct point2d* pt )
{
    pt->y = ((p[1].x - pt->x) * p[0].y + (pt->x - p[0].x) * p[1].y) / (p[1].x - p[0].x);
    return 0;
}

int interpolate_linear_line ( struct interp1d* line, const struct point2d* p)
{
    line->m = (p[1].y - p[0].y) / ( p[1].x - p[0].x );
    line->b = p[0].y - line->m * p[0].x;

    return 0;
}

int interpolate_linear_calc ( const struct interp1d* line, struct point2d* pt)
{
    pt->y = line->m * pt->x + line->b;

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
    double *L = malloc(sizeof(double)*n);
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

    free(L);

    return 0;
}

int interpolate_poly_neville(const struct point2d* p, int n, struct point2d* q) {
    double x = q->x;

    // Setup the array of values and y values and we will calculate the triangular tableau
    double *T = malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++)
        T[i] = p[i].y;

    // Run the Neville algorithm in place
    for (int k = 0; k < n-1; k++) {
        for (int i = 0; i < n - k; i++) {
            int j = i + k + 1;
            T[i] = (x - p[j].x) * T[i] - (x - p[i].x)*T[i + 1];
            T[i] /= (p[i].x - p[j].x);
        }
    }

    q->y = T[0];

    free(T);

    return 0;
}

int interpolate_poly_newton(const struct points2d* p, struct point2d* q) {
    double *x = p->x;
    int n = p->n;
    double xf = q->x;

    // Allocate F and copy over values of y
    double *F = malloc(sizeof(double)*n);
    memcpy(F, p->y, sizeof(double)*n);

    // Calculate values of F_x0, F_x1, ..., F_x0...xn
    for (int i=1; i<n; i++) {
        for (int j=n-1; j>=i; j--) {
            F[j] = (F[j] - F[j-1]) / (x[j] - x[j-i]);
        }
    }

    // Evaluate the function at q
    double yf = F[n-1];
    for (int i=n-2; i>=0; i--) {
        yf *= (xf - x[i]);
        yf += F[i];
    }

    q->y = yf;

    free(F);

    return 0;
}


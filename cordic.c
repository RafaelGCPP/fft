#include "cordic.h"
#include <math.h>

#define ITERATIONS 32

void cordic_sin_cos(double theta, double *sin, double *cos)
{
    double angle = M_PI / 4;
    double x = 0.607252935;
    double y = 0;
    double z = theta;

    for (int i = 0; i < ITERATIONS; i++)
    {
        double d = (z >= 0) ? -1 : 1;
        double tx = x - d * y * pow(2, -i);
        double ty = y + d * x * pow(2, -i);
        double tz = z - d * angle;

        x = tx;
        y = ty;
        z = tz;

        angle /= 2;
    }

    *sin = y;
    *cos = x;
}

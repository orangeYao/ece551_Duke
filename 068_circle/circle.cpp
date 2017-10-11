#include "circle.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

Circle::Circle (): radius(0)
{
}

Circle::Circle (Point &p1, double r): p(p1), radius(r) 
{
}

void Circle::move (double dx, double dy)
{
  p.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle)
{
  double R = radius; 
  double r = otherCircle.radius;
  double d = p.distanceFrom(otherCircle.p);

  if (this == & otherCircle)
    return pow(R, 2) * atan(1)*4;

  if (d < abs(R - r))
    return std::min(pow(R, 2), pow(r, 2))* atan(1)*4; // *pi

  double p1 = r*r*acos((d*d + r*r - R*R)/(2*d*r));
  double p2 = R*R*acos((d*d + R*R - r*r)/(2*d*R)); 
  double p3 = 0.5*pow((-d+r+R)*(d+r-R)*(d-r+R)*(d+r+R), 0.5);

  return p1 + p2 - p3;
}


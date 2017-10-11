#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "point.h"

class Circle {
  private:
    Point p;
    const double radius;

  public:
    Circle ();
    Circle (Point &p1, double r);
    void move (double dx, double dy);
    double intersectionArea(const Circle & otherCircle);

};

#endif

#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"
struct Shape
{
public:
  virtual void getArea();
  virtual void getFrameRect();
  virtual void move(point_t concrete_point);
  virtual void move(double dx, double dy);
  virtual void scale();
};
#endif

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "regular.hpp"

namespace maslov
{
  struct Rectangle final: public Shape
  {
    Rectangle(point_t lowerLeftCorner, point_t upperRightCorner);
    ~Rectangle() override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t s) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
   private:
    Regular ** regularArray_;
    void clear(size_t count);
    size_t n_, nWidth_;
  };
}

#endif

#include "shape.hpp"
#include <stdexcept>
void nikonov::Shape::scale(double k)
{
  if (k <= 0)
  {
    throw std::logic_error("Scale denied: k must be more than zero");
  }
  doScale(k);
}
void nikonov::Shape::scaleWithoutCheck(double k)
{
  doScale(k);
}

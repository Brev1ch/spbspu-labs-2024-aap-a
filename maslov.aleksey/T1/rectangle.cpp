#include "rectangle.hpp"

double maslov::Rectangle::getArea() const
{
  return getFrameRect().height * getFrameRect().width;
}
maslov::rectangle_t maslov::Rectangle::getFrameRect() const
{
  double height = upperRightCorner_.y - lowerLeftCorner_.y;
  double width = upperRightCorner_.x - lowerLeftCorner_.x;
  double centerY = lowerLeftCorner_.y + height / 2.0;
  double centerX = lowerLeftCorner_.x + width / 2.0;
  return {width, height, {centerX, centerY}};
}
void maslov::Rectangle::move(point_t s)
{
  point_t center = getFrameRect().pos;
  double dx = s.x - center.x;
  double dy = s.y - center.y;
  lowerLeftCorner_ = {lowerLeftCorner_.x + dx, lowerLeftCorner_.y + dy};
  upperRightCorner_ = {upperRightCorner_.x + dx, upperRightCorner_.y + dy};
}
void maslov::Rectangle::move(double dx, double dy)
{
  lowerLeftCorner_ = {lowerLeftCorner_.x + dx, lowerLeftCorner_.y + dy};
  upperRightCorner_ = {upperRightCorner_.x + dx, upperRightCorner_.y + dy};
}
void maslov::Rectangle::scale(double k)
{
  point_t center = getFrameRect().pos;
  lowerLeftCorner_.x = center.x + (lowerLeftCorner_.x - center.x) * k;
  lowerLeftCorner_.y = center.y + (lowerLeftCorner_.y - center.y) * k;
  upperRightCorner_.x = center.x + (upperRightCorner_.x - center.x) * k;
  upperRightCorner_.y = center.y + (upperRightCorner_.y - center.y) * k;
}

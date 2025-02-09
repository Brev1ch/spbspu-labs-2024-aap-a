#include "composite-shape.hpp"
#include <limits>
#include <stdexcept>
#include "shape.hpp"
alymova::CompositeShape::CompositeShape():
  size_(0),
  capacity_(10),
  shapes_(new Shape*[capacity_])
{}
/*{
  try
  {
    shapes_ = new Shape*[capacity_];
  }
  catch (const std::bad_alloc& e)
  {
    clear(shapes_);
    throw std::runtime_error("Creating composition of shapes error");
  }
}*/
alymova::CompositeShape::CompositeShape(const CompositeShape& comp_shape):
  size_(comp_shape.size_),
  capacity_(comp_shape.capacity_),
  shapes_(nullptr)
{
  try
  {
    shapes_ = new Shape*[capacity_]();
    copyArray(comp_shape.shapes_);
  }
  catch (...)
  {
    size_ = 0;
    capacity_ = 10;
    clear(shapes_);
    throw std::runtime_error("Creating coping composition of shapes error");;
  }
}
alymova::CompositeShape::CompositeShape(const CompositeShape&& comp_shape):
  size_(comp_shape.size_),
  capacity_(comp_shape.capacity_),
  shapes_(nullptr)
{
  try
  {
    shapes_ = new Shape*[capacity_];
    copyArray(comp_shape.shapes_);
  }
  catch (...)
  {
    size_ = 0;
    capacity_ = 10;
    clear(shapes_);
    throw std::runtime_error("Creating moving composition of shapes error");
  }
}
alymova::CompositeShape::~CompositeShape()
{
  clear(shapes_);
}
alymova::CompositeShape& alymova::CompositeShape::operator=(const CompositeShape& comp_shape)
{
  try
  {
    if (this != &comp_shape)
    {
      CompositeShape copy{comp_shape};
      capacity_ = comp_shape.capacity_;
      size_ = comp_shape.size_;
      clear(shapes_);
      shapes_ = new Shape*[comp_shape.capacity_];
      swap(copy);
    }
    return *this;
  }
  catch (const std::bad_alloc& e)
  {
    clear(shapes_);
    throw std::runtime_error("Copying assigment error");
  }
}
alymova::CompositeShape& alymova::CompositeShape::operator=(const CompositeShape&& comp_shape)
{
  try
  {
    CompositeShape copy{comp_shape};
    capacity_ = comp_shape.capacity_;
    size_ = comp_shape.size_;
    clear(shapes_);
    shapes_ = new Shape*[comp_shape.capacity_];
    swap(copy);
    return *this;
  }
  catch (const std::bad_alloc& e)
  {
    clear(shapes_);
    throw std::runtime_error("Moving assigment error");
  }
}
alymova::Shape* alymova::CompositeShape::operator[](size_t id) noexcept
{
  return shapes_[id];
}
const alymova::Shape* alymova::CompositeShape::operator[](size_t id) const noexcept
{
  return shapes_[id];
}
double alymova::CompositeShape::getArea() const noexcept
{
  double area_sum = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    area_sum += shapes_[i]->getArea();
  }
  return area_sum;
}
alymova::rectangle_t alymova::CompositeShape::getFrameRect() const noexcept
{
  double low_left_x = std::numeric_limits< double >::max();
  double low_left_y = std::numeric_limits< double >::max();
  double upp_right_x = std::numeric_limits< double >::min();
  double upp_right_y = std::numeric_limits< double >::min();
  for (size_t i = 0; i < size_; i++)
  {
    rectangle_t rect = {shapes_[i]->getFrameRect()};
    low_left_x = std::min(low_left_x, getLowLeftFrameRect(rect).x);
    low_left_y = std::min(low_left_y, getLowLeftFrameRect(rect).y);
    upp_right_x = std::max(upp_right_x, getUppRightFrameRect(rect).x);
    upp_right_y = std::max(upp_right_x, getUppRightFrameRect(rect).y);
  }
  double width = upp_right_x - low_left_x;
  double height = upp_right_y - low_left_y;
  return rectangle_t{width, height, point_t{upp_right_x - width / 2.0, upp_right_y - height / 2.0}};
}
void alymova::CompositeShape::move(point_t point) noexcept
{
  point_t pos = getFrameRect().pos;
  double shift_x = point.x - pos.x;
  double shift_y = point.y - pos.y;
  move(shift_x, shift_y);
}
void alymova::CompositeShape::move(double shift_x, double shift_y) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i]->move(shift_x, shift_y);
  }
}
void alymova::CompositeShape::scale(double ratio)
{
  checkRatioScale(ratio);
  unsafeScale(ratio);
}
void alymova::CompositeShape::unsafeScale(double ratio) noexcept
{
  point_t pos = getFrameRect().pos;
  alymova::unsafeScale(*this, pos, ratio);
}
void alymova::CompositeShape::push_back(Shape* shp)
{
  if (size_ == capacity_)
  {
    int ratio = 2;
    Shape** shapes_new = new Shape*[capacity_ * ratio]();
    for (size_t i = 0; i < size_; i++)
    {
      shapes_new[i] = shapes_[i];
    }
    clear(shapes_);
    shapes_ = shapes_new;
    capacity_ *= ratio;
  }
  shapes_[size_] = shp;
  size_++;
    /*catch (const std::bad_alloc& e)
    {
      capacity_ /= ratio;
      clear(shapes_new);
      throw std::runtime_error("Adding element error");
    }*/
}
void alymova::CompositeShape::pop_back() noexcept
{
  if (size_ > 0)
  {
    delete shapes_[size_ - 1];
    size_--;
  }
}
alymova::Shape* alymova::CompositeShape::at(size_t id)
{
  if (id > (size_ - 1))
  {
    throw std::out_of_range("Incorrect index");
  }
  return shapes_[id];
}
bool alymova::CompositeShape::empty() const noexcept
{
  return size_ == 0;
}
size_t alymova::CompositeShape::size() const noexcept
{
  return size_;
}
void alymova::CompositeShape::copyArray(const Shape* const* other_shapes)
{
  for (size_t i = 0; i < size_; i++)
  {
    delete shapes_[i];
    try
    {
      shapes_[i] = other_shapes[i]->clone();
    }
    catch (...)
    {
      delete shapes_[i];
      throw std::runtime_error("Coping error");
    }
  }
}
void alymova::CompositeShape::swap(CompositeShape& copy) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    shapes_[i] = copy[i];
    copy.do_null(i);
  }
}
void alymova::CompositeShape::do_null(size_t id) noexcept
{
  shapes_[id] = nullptr;
}
void alymova::CompositeShape::clear(Shape** shapes) noexcept
{
  for (size_t i = 0; i < size_; i++)
  {
    delete shapes[i];
  }
  delete[] shapes;
}

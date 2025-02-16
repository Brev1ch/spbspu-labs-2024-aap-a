#include "inputProcess.hpp"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "fabrics.hpp"
constexpr size_t figures_cnt = 3;
void alymova::makeShape(std::istream& in, CompositeShape& shapes, bool& wrong_shape_flag, double* scale_params)
{
  Creator* fabric = new CreatorSpecial();

  bool scale_flag = false;
  while (!scale_flag)
  {
    if (in.eof())
    {
      throw std::logic_error("Command SCALE must be described");
    }
    std::string type;
    in >> type;

    Shape* shape = nullptr;
    try
    {
      shape = fabric->create(type, in);
      shapes.push_back(shape);

      if (type == "SCALE")
      {
        readParameters(in, scale_params, 3);
        scale_flag = true;
      }
    }
    catch (const std::logic_error& e)
    {
      wrong_shape_flag = true;
      break;
    }
    catch (const std::bad_alloc& e)
    {
      delete shape;
      delete fabric;
      throw;
    }
  }
  delete fabric;
}
void alymova::print(std::ostream& out, const Shape* shape)
{
  rectangle_t rect = shape->getFrameRect();
  out << " " << getLowLeftFrameRect(rect).x;
  out << " " << getLowLeftFrameRect(rect).y;
  out << " " << getUppRightFrameRect(rect).x;
  out << " " << getUppRightFrameRect(rect).y;
}
void alymova::print(std::ostream& out, const CompositeShape& shapes)
{
  size_t size = shapes.size();
  double area = shapes.getArea();
  out << std::setprecision(1) << std::fixed;
  out << area;
  for (size_t i = 0; i < size; i++)
  {
    print(out, shapes[i]);
  }
}

#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "shape.hpp"
#include "inputProcess.hpp"
#include "composite-shape.hpp"
int main()
{
  try
  {
    alymova::CompositeShape shapes;
    bool wrong_shape_flag = false;
    double scale_params[3] = {};
    alymova::makeShape(std::cin, shapes, wrong_shape_flag, scale_params);
    if (shapes.empty())
    {
      std::cerr << "Nothing to scale\n";
      return 1;
    }
    alymova::print(std::cout, shapes);
    std::cout << "\n";
    alymova::scale(shapes, alymova::point_t{scale_params[0], scale_params[1]}, scale_params[2]);
    alymova::print(std::cout, shapes);
    std::cout << "\n";
    if (wrong_shape_flag)
    {
      std::cerr << "Incorrect description of the shapes\n";
    }
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Memory allocate error\n";
    return 1;
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }


  /*constexpr int max_size = 1000;
  alymova::Shape* shapess[max_size] = {};
  size_t shapes_now = 0;
  double scale_params[3] = {};
  bool wrong_shape_flag = false;
  try
  {
    alymova::makeShape(std::cin, shapes, wrong_shape_flag, scale_params);
  }
  catch (const std::logic_error& e)
  {
    clear(shapes);
    std::cerr << e.what() << "\n";
    return 1;
  }
  if (shapes_now == 0)
  {
    std::cerr << "Nothing to scale\n";
    return 1;
  }
  alymova::print(std::cout, shapes);
  std::cout << "\n";
  try
  {
    alymova::scale(shapes, alymova::point_t{scale_params[0], scale_params[1]}, scale_params[2]);
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    alymova::clear(shapes);
    return 1;
  }
  alymova::print(std::cout, shapes);
  std::cout << "\n";
  if (wrong_shape_flag)
  {
    std::cerr << "Incorrect description of the shapes\n";
  }
  clear(shapes);*/
}

#pragma once

#include<limits>

namespace ConsoleAppRansacIINamespace {
namespace Core {


/**
* @brief A small value used to compare floating point numbers.
*
* @see https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
*/
constexpr double epsilon{ std::numeric_limits<double>::epsilon() };

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
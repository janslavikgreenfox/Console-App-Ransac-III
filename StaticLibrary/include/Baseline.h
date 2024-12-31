#pragma once

#include<limits>

namespace ConsoleAppRansacIINamespace {
namespace Core {

typedef double	columnValuesType;
typedef int		headerRowIndexType;
typedef int		valuesRowIndexType;
typedef int		columnIndexType;

enum CTestResult {
	Success = 0,
	Failure = 1
};

constexpr double epsilon{ std::numeric_limits<double>::epsilon() };

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
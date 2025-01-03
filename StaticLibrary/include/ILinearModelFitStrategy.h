#pragma once
#include "Table.h"
#include "Column.h"
#include "LinearModel.h"

using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;
using Column = ConsoleAppRansacIINamespace::Core::Column;

namespace ConsoleAppRansacIINamespace {
namespace Fitting {

/**
* @class ILinearModelFitStrategy
* @brief An interface for a fitting algorithm/strategy for a linear model to a set of data points.
*/
class ILinearModelFitStrategy {
  public:
    /**
	* @ brief Destructor
    */
    virtual ~ILinearModelFitStrategy() = default;

    /**
	* @brief Fits a linear model to a set of data points.
	* @param model The linear model to fit.
	* @param abcissa The abcissa values of the data points.
	* @param ordinate The ordinate values of the data points.
    */
	virtual void fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) = 0;
};

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace
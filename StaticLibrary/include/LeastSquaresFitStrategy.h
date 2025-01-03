#pragma once

#include "ILinearModelFitStrategy.h"

namespace ConsoleAppRansacIINamespace {
namespace Fitting {

/**
* @class LeastSquaresFitStrategy
* @brief The Least Squares fitting algorithm/strategy for a linear model to a set of data points using the least squares method.
*/
class LeastSquaresFitStrategy : public ILinearModelFitStrategy {
public:
	/**
    * @brief Fits a linear model to a set of data points using the Least Squares algorithm.
    * @param model The linear model to fit.
    * @param abcissa The abcissa values of the data points.
    * @param ordinate The ordinate values of the data points.
    */
	virtual void fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) override;
};

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace

#pragma once

#include "ILinearModelFitStrategy.h"

namespace ConsoleAppRansacIINamespace {
namespace Fitting {

class LeastSquaresFitStrategy : public ILinearModelFitStrategy {
public:
	virtual void fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) override;
};

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace

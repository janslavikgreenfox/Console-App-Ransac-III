#pragma once
#include "Table.h"
#include "Column.h"
#include "LinearModel.h"

using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;
using Column = ConsoleAppRansacIINamespace::Core::Column;

namespace ConsoleAppRansacIINamespace {
namespace Fitting {

class ILinearModelFitStrategy {
  public:
    virtual ~ILinearModelFitStrategy() = default;
	virtual void fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) = 0;
};

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace
// Copyright (C) 2025 Jan Slavik, Blackstone Labs
// 
// This file is part of the Console-App-Ransac-III project.
// 
// Licensed under the MIT License. You may obtain a copy of the License at:
// 
//     https://opensource.org/licenses/MIT
// 
// This software is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
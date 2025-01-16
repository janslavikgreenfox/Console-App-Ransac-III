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

#include "LeastSquaresFitStrategy.h"
#include "LinearModel.h"

using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;
using Column = ConsoleAppRansacIINamespace::Core::Column;

namespace ConsoleAppRansacIINamespace {
namespace Fitting {

void LeastSquaresFitStrategy::fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) {
	double abcissaAverage = abcissa.getAverage();
	double ordinateAverage = ordinate.getAverage();

	double numerator = 0;
	double denominator = 0;
	size_t sharedNumberOfRows = abcissa.getNoRows();
	for (size_t sharedIndex = 0; sharedIndex < sharedNumberOfRows; sharedIndex++) {
		double abcissaCentralMoment = abcissa.getValueForOneSpecifiedRow(sharedIndex) - abcissaAverage;
		double ordinateCentralMoment = ordinate.getValueForOneSpecifiedRow(sharedIndex) - ordinateAverage;
		numerator += abcissaCentralMoment * ordinateCentralMoment;
		denominator += abcissaCentralMoment * abcissaCentralMoment;
	}
	model.setSlope(numerator / denominator);
	model.setYIntercept(ordinateAverage - model.getSlope() * abcissaAverage);
}

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace
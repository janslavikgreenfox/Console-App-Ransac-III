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

#include "RANSACFitStrategy.h"
#include "LeastSquaresFitStrategy.h"

#include <set>
#include <random>
#include <algorithm>

namespace ConsoleAppRansacIINamespace {
namespace Fitting {

RANSACParameters parameters{};



LinearModel RANSACFitStrategy::fitLinearModel(const Column& abcissa, const Column& ordinate) {
	int iterations = 0;
	LinearModel bestModel;
	double bestErr = std::numeric_limits<double>::max();

	while (iterations < parameters.getNumberOfIterations()) {
		vector<size_t> randomIndexesSample = 
			//ConsoleAppRansacIINamespace::Core::getRandomIndexes(parameters.getNumberOfRandomSelectedPoints(), ordinate.getNoOfRows());
		    getRandomIndexes(parameters.getNumberOfRandomSelectedPoints(), ordinate.getNoOfRows());
		Column sampledAbcissa  = abcissa.getSpecifiedRows(randomIndexesSample);
		Column sampledOrdinate = ordinate.getSpecifiedRows(randomIndexesSample);
		//LinearModel maybeModel;
		LeastSquaresFitStrategy maybeStrategy;
		LinearModel maybeModel = maybeStrategy.fitLinearModel(sampledAbcissa, sampledOrdinate);
		//maybeModel.fitModelByOrdinaryLeastSquares(sampledAbcissa, sampledOrdinate);

		std::set<size_t, std::less<>> confirmedInliners;
		for (size_t i = 0; i < abcissa.getNoOfRows(); i++) {
			double modelValueX = abcissa.getOneRow(i);
			double modelValueY = maybeModel.getValueAt(modelValueX);
			double Y = ordinate.getOneRow(i);
			if (abs(modelValueY - Y) < parameters.getTresholdValueToBeInlier()) {
				confirmedInliners.insert(i);
			}
		}
		if (confirmedInliners.size() >= parameters.getNumberOfInliersToWellFit()) {
			vector<size_t> inliners(confirmedInliners.begin(), confirmedInliners.end());
			Column betterAbcissa = abcissa.getSpecifiedRows(inliners);
			Column betterOrdinate = ordinate.getSpecifiedRows(inliners);
			LeastSquaresFitStrategy betterStrategy;
			LinearModel betterModel = betterStrategy.fitLinearModel(betterAbcissa, betterOrdinate);
			//betterModel.fitModelByOrdinaryLeastSquares(betterAbcissa, betterOrdinate);
			double betterFit = betterModel.sumOfSquaredResiduals(betterAbcissa, betterOrdinate);
			if (betterFit < bestErr) {
				bestModel = betterModel;
				bestErr   = betterFit;
			}
		}
		iterations++;
	}
	return bestModel;
}

//namespace columnUtils {
std::vector<size_t> RANSACFitStrategy::getRandomIndexes(size_t numberOfSelectedPoints, size_t noOfRows) {
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<size_t> distribution(0, noOfRows - 1);
	std::set<size_t, std::less<>> selectedIndexes;
	while (selectedIndexes.size() < numberOfSelectedPoints) {
		selectedIndexes.insert(distribution(generator));
	}
	std::vector<size_t> orderedSelection(selectedIndexes.begin(), selectedIndexes.end());
	std::sort(orderedSelection.begin(), orderedSelection.end());
	return orderedSelection;
}
//}

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace
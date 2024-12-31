#include "RANSACFitStrategy.h"
#include "LeastSquaresFitStrategy.h"

#include <set>

namespace ConsoleAppRansacIINamespace {
namespace Fitting {

RANSACParameters parameters{};



void RANSACFitStrategy::fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) {
	int iterations = 0;
	LinearModel bestModel;
	double bestErr = std::numeric_limits<double>::max();

	while (iterations < parameters.getNumberOfIterations()) {
		vector<size_t> randomIndexesSample = 
			ConsoleAppRansacIINamespace::Core::getRandomIndexes(parameters.getNumberOfRandomSelectedPoints(), ordinate.getNoRows());
		Column sampledAbcissa  = abcissa.getValuesForSpecifiedRows(randomIndexesSample);
		Column sampledOrdinate = ordinate.getValuesForSpecifiedRows(randomIndexesSample);
		LinearModel maybeModel;
		LeastSquaresFitStrategy maybeStrategy;
		maybeStrategy.fitModel(maybeModel, sampledAbcissa, sampledOrdinate);
		//maybeModel.fitModelByOrdinaryLeastSquares(sampledAbcissa, sampledOrdinate);

		std::set<size_t, std::less<>> confirmedInliners;
		for (size_t i = 0; i < abcissa.getNoRows(); i++) {
			double modelValueX = abcissa.getValueForOneSpecifiedRow(i);
			double modelValueY = maybeModel.getValueAt(modelValueX);
			double Y = ordinate.getValueForOneSpecifiedRow(i);
			if (abs(modelValueY - Y) < parameters.getTresholdValueToBeInlier()) {
				confirmedInliners.insert(i);
			}
		}
		if (confirmedInliners.size() >= parameters.getNumberOfInliersToWellFit()) {
			vector<size_t> inliners(confirmedInliners.begin(), confirmedInliners.end());
			Column betterAbcissa = abcissa.getValuesForSpecifiedRows(inliners);
			Column betterOrdinate = ordinate.getValuesForSpecifiedRows(inliners);
			LinearModel betterModel;
			LeastSquaresFitStrategy betterStrategy;
			betterStrategy.fitModel(betterModel, betterAbcissa, betterOrdinate);
			//betterModel.fitModelByOrdinaryLeastSquares(betterAbcissa, betterOrdinate);
			double betterFit = betterModel.sumOfSquaredResiduals(betterAbcissa, betterOrdinate);
			if (betterFit < bestErr) {
				bestModel = betterModel;
				bestErr   = betterFit;
			}
		}
		iterations++;
	}
	//return bestModel;
	model = bestModel;
}


} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace
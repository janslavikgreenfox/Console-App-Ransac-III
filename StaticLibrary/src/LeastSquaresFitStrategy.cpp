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
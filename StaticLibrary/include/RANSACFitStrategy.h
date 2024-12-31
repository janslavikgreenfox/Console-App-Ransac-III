#pragma once

#include "ILinearModelFitStrategy.h"

using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;
using Column = ConsoleAppRansacIINamespace::Core::Column;   

namespace ConsoleAppRansacIINamespace {
namespace Fitting {	

class RANSACParameters {
private:
	int numberOfIterations;
	int numberOfRandomSelectedPoints;
	double tresholdValueToBeInlier;
	int numberOfInliersToWellFit;

public:
	RANSACParameters(
		int maxIt = 1,
		int minPointsToEstimate = 2,
		double inlierThreshold = 1e9,
		int numOfInliers = 2) :
		numberOfIterations{ maxIt },
		numberOfRandomSelectedPoints{ minPointsToEstimate },
		tresholdValueToBeInlier{ inlierThreshold },
		numberOfInliersToWellFit{ numOfInliers }
	{}

	int getNumberOfIterations() const {
		return numberOfIterations;
	}

	int getNumberOfRandomSelectedPoints() const {
		return numberOfRandomSelectedPoints;
	}

	double getTresholdValueToBeInlier() const {
		return tresholdValueToBeInlier;
	}

	int getNumberOfInliersToWellFit() const {
		return numberOfInliersToWellFit;
	}
};

class RANSACFitStrategy : public ILinearModelFitStrategy {
public:
    virtual void fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) override;
};

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace
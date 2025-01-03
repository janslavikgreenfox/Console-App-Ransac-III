#pragma once

#include "ILinearModelFitStrategy.h"

using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;
using Column = ConsoleAppRansacIINamespace::Core::Column;   

namespace ConsoleAppRansacIINamespace {
namespace Fitting {	

/**
* @class RANSACParameters
* @brief The parameters for the RANSAC algorithm.
*/
class RANSACParameters {
private:
	/**
	* @brief The number of iterations to run the RANSAC algorithm.
	*/

	int numberOfIterations;
	/**
	* @brief The minimum number of points to estimate the model.
	*/
	int numberOfRandomSelectedPoints;

	/**
	* @brief The threshold value to be considered as an inlier.
	*/
	double tresholdValueToBeInlier;

	/**
	* @brief The number of inliers to consider the model as well fit.
	*/
	int numberOfInliersToWellFit;

public:
	/**
	* @brief Constructor.
	* @param maxIt The number of iterations to run the RANSAC algorithm.
	* @param minPointsToEstimate The minimum number of points to estimate the model.
	* @param inlierThreshold The threshold value to be considered as an inlier.
	* @param numOfInliers The number of inliers to consider the model as well fit.
	*/
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

	/**
	* @brief Gets the number of iterations to run the RANSAC algorithm.
	* @return The number of iterations.
	*/
	int getNumberOfIterations() const {
		return numberOfIterations;
	}

	/**
	* @brief Gets the minimum number of points to estimate the model.
	* @return The minimum number of points .
	*/
	int getNumberOfRandomSelectedPoints() const {
		return numberOfRandomSelectedPoints;
	}

	/**
	* @brief Gets the threshold value to be considered as an inlier.
	* @return The threshold value.
	*/
	double getTresholdValueToBeInlier() const {
		return tresholdValueToBeInlier;
	}

	/**
	* @brief Gets the number of inliers to consider the model as well fit.
	* 
	*/
	int getNumberOfInliersToWellFit() const {
		return numberOfInliersToWellFit;
	}
};

/**
* @class RANSACFitStrategy
* @brief The RANSAC fitting algorithm/strategy for a linear model to a set of data points using the RANSAC method.
*/
class RANSACFitStrategy : public ILinearModelFitStrategy {
public:
	/**
    * @brief Fits a linear model to a set of data points using the RANSAC algorithm.
    * @param model The linear model to fit.
    * @param abcissa The abcissa values of the data points.
    * @param ordinate The ordinate values of the data points.
    */
    virtual void fitModel(LinearModel& model, const Column& abcissa, const Column& ordinate) override;
};

} // namespace Fitting
} // namespace ConsoleAppRansacIINamespace
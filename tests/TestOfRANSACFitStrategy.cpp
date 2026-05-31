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

#include "Column.h"
#include "Table.h"
#include "RANSACFitStrategy.h"
#include "CppUnitTest.h"

#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using Column = ConsoleAppRansacIINamespace::Core::Column;
using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;
using RANSACFitStrategy = ConsoleAppRansacIINamespace::Fitting::RANSACFitStrategy;
using RANSACParameters = ConsoleAppRansacIINamespace::Fitting::RANSACParameters;

namespace UnitTest
{
	TEST_CLASS(RANSACFitTest)
	{
	public:

		TEST_METHOD(TrivialCase)
		{
			// Arrange
			std::vector<double> x{ 0.0, 1.0 };
			Column xColumn{ x, "Column X" };
			std::vector<double> y{ 2.0, 0.0 };
			Column yColumn{ y, "Column Y" };
			constexpr double expectedSlope{ -2.0 };
			constexpr double expectedYIntercept{ 2.0 };

			LinearModel linearModel;
			RANSACFitStrategy ransacFitStrategy;

			// Act
			linearModel = ransacFitStrategy.fitLinearModel(xColumn, yColumn);

			// Assert
			Assert::AreEqual(expectedSlope, linearModel.getSlope());
			Assert::AreEqual(expectedYIntercept, linearModel.getValueAt0());
		}

		TEST_METHOD(PureLinearCase)
		{
			// Arrange
			constexpr size_t sizeOfData = 101;
			std::vector<double> xPureLinearDependency(sizeOfData);
			constexpr double incrementStepSize = 0.1;
			double value = 0;
			std::generate(
				xPureLinearDependency.begin(),
				xPureLinearDependency.end(),
				[&value, incrementStepSize]() {
					double current = value;
					value += incrementStepSize;
					return current;
				}
			);
			Column xColumnPureLinear{ xPureLinearDependency, "Column X" };
			//
			// y = 2x - 1
			constexpr double pureDependencyIntercept = -1.0;
			constexpr double pureDependencySlope = 2.0;
			std::vector<double> yPureLinearDependency(xPureLinearDependency.size());
			std::transform(
				xPureLinearDependency.begin(),
				xPureLinearDependency.end(),
				yPureLinearDependency.begin(),
				[pureDependencySlope,pureDependencyIntercept]
				(double x) {return pureDependencySlope * x + pureDependencyIntercept; }
			);
			Column yColumnPureLinear{ yPureLinearDependency, "Column Y" };

			// Act
			RANSACParameters ransacParam(1,2,1e9,2);
			RANSACFitStrategy ransacFitStrategy;
			LinearModel ransac = ransacFitStrategy.fitLinearModel(xColumnPureLinear, yColumnPureLinear);

			// Assert
			using ConsoleAppRansacIINamespace::Core::epsilon;
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(
					ransac.getSlope(), pureDependencySlope, 100*epsilon
				)
			);
		    
		    Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(
					ransac.getValueAt0(), pureDependencyIntercept, 100*epsilon
				)
		    );
			//Assert::AreEqual(ransac.getSlope(), pureDependencySlope);
			//Assert::AreEqual(ransac.getValueAt0(), pureDependencyIntercept);
		}

		//High Inlier Proportion :
		//If the data contains very few outliers, RANSAC may perform unnecessarily 
		// because it is computationally expensive and may not provide better results than Least Squares.
		//	
		//	High Outlier Proportion :
		//If the proportion of inliers is very low(e.g., less than 50 %), 
		// RANSAC may fail to find a good model, as it may never randomly sample a subset consisting solely of inliers.
		//	
		//	Ambiguous Models :
		//If multiple models fit the data equally well(e.g., overlapping clusters 
		// or multiple valid patterns), RANSAC might select a suboptimal model due to randomness.
		//	
		//	Threshold Sensitivity :
		//The choice of the inlier threshold(distance from the model 
		// to classify a point as an inlier) can dramatically affect results.
		// A too - large threshold may classify outliers as inliers, 
		// while a too - small threshold may exclude valid inliers.
		//	
		//	Computational Complexity :
		//In cases with a large dataset and complex models, 
		// RANSAC may become computationally expensive due to its iterative nature.
	};
}
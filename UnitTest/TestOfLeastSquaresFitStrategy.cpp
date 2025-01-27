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
#include "Common.h"
#include "Table.h"
#include "LeastSquaresFitStrategy.h"
#include "CppUnitTest.h"
#include <random>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using Column = ConsoleAppRansacIINamespace::Core::Column;
using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;
using LeastSquaresFitStrategy = ConsoleAppRansacIINamespace::Fitting::LeastSquaresFitStrategy;



namespace UnitTest
{
	TEST_CLASS(LeastSquaresFitTest)
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
			LeastSquaresFitStrategy leastSquareFitStrategy;

			// Act
			linearModel = leastSquareFitStrategy.fitLinearModel(xColumn, yColumn);
			
			// Assert
			Assert::AreEqual(expectedSlope, linearModel.getSlope());
			Assert::AreEqual(expectedYIntercept, linearModel.getValueAt0());
		}

		TEST_METHOD(TrivialCaseFor3Points)
		{
			// Arrange
			std::vector<double> x{ 0.0, 1.0, 2.0 };
			Column xColumn{ x, "Column X" };
			std::vector<double> y{ -1.0, 0.0, 1.0 };
			Column yColumn{ y, "Column Y" };
			constexpr double expectedSlope{ +1.0 };
			constexpr double expectedYIntercept{ -1.0 };

			LinearModel linearModel;
			LeastSquaresFitStrategy leastSquareFitStrategy;
			
			// Act
			linearModel = leastSquareFitStrategy.fitLinearModel(xColumn, yColumn);

			// Assert
			Assert::AreEqual(expectedSlope, linearModel.getSlope());
			Assert::AreEqual(expectedYIntercept, linearModel.getValueAt0());
		}

		/**
		* Outliers
		* The least squares method is highly sensitive to outliers. 
		* A single outlier can disproportionately affect the results 
		* because squaring the residuals amplifies large errors.
        *  Example: In a linear regression with most points forming a 
		*  straight line but one point far off the line, the model may 
		*  adjust disproportionately to fit that outlier.
		*/
		TEST_METHOD(Outlier)
		{
			// Arrange
			std::vector<double> xPureLinearDependency
			    { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
			Column xColumnPureLinear{ xPureLinearDependency, "Column X" };
			// y = 2x - 1
			std::vector<double> yPureLinearDependency
			    { -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0 };
			Column yColumnPureLinear{ yPureLinearDependency, "Column Y" };

			LeastSquaresFitStrategy leastSquareFitStrategy;
			LinearModel fromPureLinearDepency 
		        = leastSquareFitStrategy.fitLinearModel(xColumnPureLinear, yColumnPureLinear);

			constexpr double outlierX{ 0.5 };
			Column xWithOutlier{ xColumnPureLinear };
			xWithOutlier.addRow(outlierX);

			constexpr double outlierY{ 10 };
			Column yWithOutlier{ yColumnPureLinear };
			yWithOutlier.addRow(outlierY);

			constexpr double expectedSlopeWithOutlier{ 2.0 };
			constexpr double expectedYInterceptWithOutlier{ -0.16666666666666666 };

			// Act
			LinearModel withOutlier
				= leastSquareFitStrategy.fitLinearModel(xWithOutlier, yWithOutlier);	

			// Assert
			Assert::AreEqual(expectedSlopeWithOutlier, withOutlier.getSlope());
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(
				    expectedYInterceptWithOutlier, withOutlier.getValueAt0()
				)
			);
		}

		/*Ill - Conditioned Systems :

		If the matrix of predictors(in linear regression) is nearly singular
		(e.g., due to multicollinearity or highly correlated predictors),
			the solution may become unstable or numerically inaccurate.*/
		TEST_METHOD(IllConditionedCase)
		{
			Assert::IsTrue(false);
		}


		/** Non - Gaussian Noise :
        *
		* Least squares assumes that the errors(residuals) are normally distributed 
		* with constant variance.If the noise follows a different distribution
		* (e.g., heavy - tailed distributions like Cauchy), the method may fail 
		* to provide accurate results.
		*/
		std::vector<double> generateCauchyNoise(int size, double location, double scale, unsigned seed)
		{
			//std::random_device rd;
			std::mt19937 gen(seed);
			std::cauchy_distribution<double> cauchy(location, scale);
			std::vector<double> noise(size);
			for (int i = 0; i < size; i++)
			{
				noise[i] = cauchy(gen);
			}
			return noise;
		}

		TEST_METHOD(NonGaussianNoise)
		{
			// Arrange
			std::vector<double> xPureLinearDependency
			    { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
			Column xColumn{xPureLinearDependency, "Column X" };
			std::vector<double>  yPureLinearDependency
			    { -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0 };
			Column yColumn{ yPureLinearDependency, "Column Y" };

			constexpr int size = 11;             // Number of noise points
			constexpr double location = 0.0;     // Location parameter (mean)
			constexpr double scale = 0.1;        // Scale parameter (spread)
			constexpr unsigned seed = 42;        // Fixed seed for reproducibility

			// Generate Cauchy noise
			std::vector<double> noise = generateCauchyNoise(size, location, scale, seed);

			std::vector<double> yWithNoise(yPureLinearDependency.size());
			std::transform(
				noise.begin(), 
				noise.end(), 
				yPureLinearDependency.begin(), 
				yWithNoise.begin(),
				[](double noise, double y) { return y + noise; }
			);
			Column yColumnWithNoise{ yWithNoise, "Column Y" };

			// Act
			LeastSquaresFitStrategy leastSquareFitStrategy;
			LinearModel linearModel = leastSquareFitStrategy.fitLinearModel(xColumn, yColumnWithNoise);

			// Assert
			constexpr double expectedSlope = 1.6543486078828931;
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(expectedSlope, linearModel.getSlope())
			);
			constexpr double expectedYIntercept = -0.91603394758318080;
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(expectedYIntercept, linearModel.getValueAt0())
			);
		}

		/*Non - Linear Models :

		Least squares works well for linear models, but in non - linear models, 
			the solution may converge to a local minimum instead of the global minimum.*/

		TEST_METHOD(NonLinearModels)
		{
			Assert::IsTrue(false);
		}


		TEST_METHOD(PerformanceTest)
		{
			Assert::IsTrue(false);
		}
	};
}
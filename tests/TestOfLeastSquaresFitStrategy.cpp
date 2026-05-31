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
		TEST_METHOD(OneOutlier)
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
			the solution may become unstable or numerically inaccurate.
		
		    (x1, y1) = (1,      2.0); 
		    (x2, y2) = (1.0001, 2.0001);
			
			Leads to the matrix A = [1    1   ]
			                        [1  1.0001]
			
			and the left side   b = [  2   ]
			                        [2.0001]

			A is almost singular, to solve the equation  A * [y-intercept slope]' = b 

		*/

		TEST_METHOD(IllConditionedCase)
		{
            // Arrange
			// First case 
			std::vector<double> xFirstCase{ 1.0, 1.0001 };
			Column xColumnFirstCase{ xFirstCase, "Column X" };
			std::vector<double> yFirstCase{ 2.0, 2.0001 };
			Column yColumnFirstCase{ yFirstCase, "Column Y" };
			constexpr double expectedSlopeFirstCase{ +1.0000000000022204 }; // approx. +1.0
			constexpr double expectedYInterceptFirstCase{ +0.99999999999777955 }; // approx +1.0

			// Second case = first case, except that y2 = 2.0001 replaced by y2 = 2.0 (smaller by 0.0001, very small perturbation)
			std::vector<double> xSecondCase{ 1.0, 1.0001 };
			Column xColumnSecondCase{ xSecondCase, "Column X" };
			std::vector<double> ySecondCase{ 2.0, 2.0 };
			Column yColumnSecondCase{ ySecondCase, "Column Y" };
			constexpr double expectedSlopeSecondCase{ +0.0 }; // approx. +2.0 = slope has doubled 
			constexpr double expectedYInterceptSecondCase{ +2.0 }; // approx +0.0 = y intercept dropped from 1.0 to 0.0

			LeastSquaresFitStrategy leastSquareFitStrategy;

			// Act
			LinearModel firstCase
				= leastSquareFitStrategy.fitLinearModel(xColumnFirstCase, yColumnFirstCase);
			LinearModel secondCase
				= leastSquareFitStrategy.fitLinearModel(xColumnSecondCase, yColumnSecondCase);
			
			// Assert
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(
					expectedSlopeFirstCase, firstCase.getSlope()
				)
			);
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(
					expectedYInterceptFirstCase, firstCase.getValueAt0()
				)
			);
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(
					expectedSlopeSecondCase, secondCase.getSlope()
				)
			);
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(
					expectedYInterceptSecondCase, secondCase.getValueAt0()
				)
			);		
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
		*
		* Least squares works well for linear models, but in non - linear models, 
		*  the solution may converge to a local minimum instead of the global minimum.
		*
		*/

		TEST_METHOD(NonLinearModels)
		{
			// Arrange
			std::vector<double> xFirstCase{ 0.0, 1.0, 2.0 };
			Column xColumnFirstCase{ xFirstCase, "Column X" };
			std::vector<double> yFirstCase(xFirstCase.size());
			std::transform(
				xFirstCase.cbegin(),
				xFirstCase.cend(),
				yFirstCase.begin(),
				[](double x) {return (1.0 + x * x); }
			);
			Column yColumnFirstCase{ yFirstCase, "Column Y" };

			// Act
			LeastSquaresFitStrategy leastSquareFitStrategy;
			LinearModel linearModel
				= leastSquareFitStrategy.fitLinearModel(xColumnFirstCase, yColumnFirstCase);

			// Assert
			constexpr double expectedYIntercept{ 0.66666666666666696 };
			constexpr double expectedSlope{ 2.0 };
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(expectedYIntercept, linearModel.getValueAt0())
			);
			Assert::IsTrue(
				ConsoleAppRansacIINamespace::Core::doublesAreEqual(expectedSlope, linearModel.getSlope())
			);
		}

		/*Performance Test:
		* 
		* 
		*/

		//TEST_METHOD(PerformanceTest)
		//{
		//	Assert::IsTrue(false);
		//}
	};
}
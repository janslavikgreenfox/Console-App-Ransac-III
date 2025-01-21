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
#include "LeastSquaresFitStrategy.h"
#include "CppUnitTest.h"

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
			leastSquareFitStrategy.fitModel(linearModel, xColumn, yColumn);
			
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
			leastSquareFitStrategy.fitModel(linearModel, xColumn, yColumn);

			// Assert
			Assert::AreEqual(expectedSlope, linearModel.getSlope());
			Assert::AreEqual(expectedYIntercept, linearModel.getValueAt0());
		}
	};
}
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

#include "Common.h"
#include "Column.h"
#include "Table.h"
#include "CppUnitTest.h"


#include <cassert>
#include <iostream>
#include <limits>
#include <algorithm>

using Column = ConsoleAppRansacIINamespace::Core::Column;
using Table = ConsoleAppRansacIINamespace::Core::Table;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(ColumnTest)
	{
	public:

		TEST_METHOD(EmptyColumn)
		{
			// Arrange
			std::cout << "testGetNoRowsForEmptyColumn()" << std::endl;
			std::vector<double> input{};
			std::string emptyColumnName{ "I'm an empty column." };
			Column emptyColumn{ input, emptyColumnName };

			// Act
			size_t actualNoOfColumns = emptyColumn.getNoOfRows();
			std::string emptyColumnHeader = emptyColumn.getHeader();
			std::vector<double> emptyColumnValues = emptyColumn.getAllRows();
			double averageOfEmptyColumn = emptyColumn.getAverage();

			// Assert
			constexpr size_t expectedNoOfRows = 0;
			Assert::AreEqual(actualNoOfColumns, expectedNoOfRows);

			Assert::AreEqual(emptyColumnName, emptyColumnHeader);

			constexpr double expectedMeanOfEmptyColumn = 0;
			Assert::AreEqual(expectedMeanOfEmptyColumn, averageOfEmptyColumn);

			//try {
			//	double oneValueFromEmptyColumn = emptyColumn.getOneRow(0);
			//}
			//catch (const Column::RowIndexOutOfBounds& e) {
			//	std::cout << e.what();
			//	cTestResult = CTestResult::Success;
			//}
			//catch (...) {
			//	return CTestResult::Failure;
			//}

			//try {
			//	Column groupOfValuesFromEmptyColumn
			//		= emptyColumn.getSpecifiedRows(std::vector<size_t>{0, 1});
			//}
			//catch (const Column::RowIndexOutOfBounds& e) {
			//	std::cout << e.what();
			//	cTestResult = CTestResult::Success;
			//}
			//catch (...) {
			//	return CTestResult::Failure;
			//}

			//// Everything passes
			//return cTestResult;
		}

		TEST_METHOD(SimpleColumn) {
			//	// Arrange
			std::cout << "testGetNoRowsForSimpleColumn()" << std::endl;
			std::vector<double> input = { 0, 1, 2 };
			std::string inputColumnName{ "Column test No. 1" };
			Column column{ input, inputColumnName };
			
			//// Act 
			size_t actualNoOfColumns = column.getNoOfRows();
			std::string actualColumnName = column.getHeader();
			double secondItem = column.getOneRow(1);
			std::vector<double> allRows = column.getAllRows();
			double average = column.getAverage();
			
			// Assert
			size_t expectedNoOfRows = input.size();
			Assert::AreEqual(actualNoOfColumns, expectedNoOfRows);
			
			Assert::AreEqual(actualColumnName, inputColumnName);
			
			Assert::AreEqual(secondItem, input.at(1));
			
			bool valuesAreEqual = (allRows == input);
			Assert::IsTrue(valuesAreEqual);
			
			double expectedSum{0};
			std::for_each(input.begin(), input.end(), [&expectedSum](double& item) {expectedSum += item; });
			Assert::AreEqual(average, expectedSum / expectedNoOfRows);
		}
	};
}

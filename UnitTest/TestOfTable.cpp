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

using Column = ConsoleAppRansacIINamespace::Core::Column;
using Table = ConsoleAppRansacIINamespace::Core::Table;


std::vector<double> shortVectorOne{ 0, 1.1, 2.2 };
Column shortColumnOne{ shortVectorOne, "First vector" };
std::vector<double> shortVectorTwo{ 3.14, 1.414, 2.718 };
Column shortColumnTwo{ shortVectorTwo, "Second vector" };
std::vector<double> longVector{ 0, 0.1, 0.2, 0.3, 0.4 };
Column longColumn{ longVector, "Long Vector" };


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TableTest) {
    public:

	    TEST_METHOD(EmptyTable) {
			// Arrange
			std::string emptyTableName{ "Empty table" };
			Table emptyTable{ emptyTableName };

			// Act
			size_t actualNoOfColumns = emptyTable.getNoOfColumns();

			// Assert
			constexpr size_t expectedNoOfColumns = 0;
			Assert::AreEqual(expectedNoOfColumns, actualNoOfColumns);

			//try {
			//	double valueFromEmptyTable = emptyTable.getCellValue(0, 0);
			//}
			//catch (const Table::ColumnIndexOutOfBounds& columnIndexOutOfBound) {
			//	Assert::AreEqual(emptyTableName, columnIndexOutOfBound.what());
			//}
			//catch (std::exception& e) {
			//	Assert::Fail();
			//}
	    }

		TEST_METHOD(AddColumnToEmptyTable) {
			// Arrange
			std::string emptyTableName{ "Empty table" };
			Table emptyTable{ emptyTableName };

			// Act
			emptyTable.appendColumn(shortColumnOne);

			// Assert
			size_t actualNoOfColumns = emptyTable.getNoOfColumns();
			constexpr size_t expectedNoOfColumns = 1;
			Assert::AreEqual(expectedNoOfColumns, actualNoOfColumns);

			size_t shortVectorOneSize = shortVectorOne.size();
			for (size_t index = 0; index < shortVectorOneSize; index++) {
				double actualValue = emptyTable.getCellValue(index, 0);
				double expectedValue = shortVectorOne.at(index);
				Assert::AreEqual(expectedValue, actualValue);
			}
		}

		TEST_METHOD(AddTwoColumnsOfSameLength) {
			// Arrange
			Table testTable{ "Test Table" };

			// Act
			testTable.appendColumn(shortColumnOne);
			testTable.appendColumn(shortColumnTwo);

			// Assert
			size_t actualNoOfColumns = testTable.getNoOfColumns();
			constexpr size_t expectedNoOfColumns = 2;
			Assert::AreEqual(expectedNoOfColumns, actualNoOfColumns);

			for (size_t columnIndex = 0; columnIndex < actualNoOfColumns; columnIndex++) {
				Column currentColumn = testTable.getColumn(columnIndex);
				size_t currentNoOfRows = currentColumn.getNoRows();
				for (size_t rowIndex = 0; rowIndex < currentNoOfRows; rowIndex++) {
					double actualValue = currentColumn.getValueForOneSpecifiedRow(rowIndex);
					double expectedValue = columnIndex == 0 ? shortVectorOne.at(rowIndex) : shortVectorTwo.at(rowIndex);
					Assert::AreEqual(expectedValue, actualValue);
				}
			}
		}

		TEST_METHOD(AddColumnLongerThanTableColumns) {
			// Arrange
			Table testTable{ "Test Table" };
			testTable.appendColumn(shortColumnOne);

			// Act
			testTable.appendColumn(longColumn);

			// Assert
			Column shortColumnFromTable = testTable.getColumn(0);
			std::vector<double> shortColumnRowsFromTable = shortColumnFromTable.getValuesForAllRows();
			std::vector<double> expectedResult{ 0, 1.1, 2.2, 0, 0 };
			bool isColumnAsExpected = std::equal(
				expectedResult.begin(), expectedResult.end(),
				shortColumnRowsFromTable.begin(), shortColumnRowsFromTable.end()
			);
			Assert::IsTrue(isColumnAsExpected);
		}

		TEST_METHOD(AddColumnShorterThanTableColumns) {
			// Arrange
			Table testTable{ "Test Table" };
			testTable.appendColumn(longColumn);

			// Act
			testTable.appendColumn(shortColumnOne);

			// Assert
			Column shortColumnFromTable = testTable.getColumn(1);
			std::vector<double> shortColumnRowsFromTable = shortColumnFromTable.getValuesForAllRows();
			std::vector<double> expectedResult{ 0, 1.1, 2.2, 0, 0 };
			bool isColumnAsExpected = std::equal(
				expectedResult.begin(), expectedResult.end(),
				shortColumnRowsFromTable.begin(), shortColumnRowsFromTable.end()
			);
			Assert::IsTrue(isColumnAsExpected);
		}

		TEST_METHOD(GetNoOfColumns) {
			// Arrange
			Table testTable{ "Test Table" };
			testTable.appendColumn(shortColumnOne);
			testTable.appendColumn(shortColumnTwo);

			// Act
			size_t actualNoOfColumns = testTable.getNoOfColumns();

			// Assert
			constexpr size_t expectedNoOfColumns = 2;
			Assert::AreEqual(expectedNoOfColumns, actualNoOfColumns);
		}

		TEST_METHOD(GetColumnOfSpecifiedIndex) {
			// Arrange
			Table testTable{ "Test Table" };
			testTable.appendColumn(shortColumnOne);
			testTable.appendColumn(shortColumnTwo);

			// Act
			Column firstColumnFromTable = testTable.getColumn(0);
			std::vector<double> actualVectorFromFirstColumn = firstColumnFromTable.getValuesForAllRows();

			Column secondColumnFromTable = testTable.getColumn(1);
			std::vector<double> actualVectorFromSecondColumn = secondColumnFromTable.getValuesForAllRows();

			// Assert
			bool isFirstColumnEqual = std::equal(
				shortVectorOne.begin(), shortVectorOne.end(),
				actualVectorFromFirstColumn.begin(), actualVectorFromFirstColumn.end()
			);
			bool isSecondColumnEqual = std::equal(
				shortVectorTwo.begin(), shortVectorTwo.end(),
				actualVectorFromSecondColumn.begin(), actualVectorFromSecondColumn.end()
			);

			Assert::IsTrue(isFirstColumnEqual);
			Assert::IsTrue(isSecondColumnEqual);
		}

		TEST_METHOD(GetCellValueFromTable) {
			// Arrange
			Table testTable{ "Test Table" };
			testTable.appendColumn(shortColumnOne);
			testTable.appendColumn(shortColumnTwo);

			constexpr size_t rowIndex = 1;
			constexpr size_t columnIndex = 0;

			// Act
			double actualValue = testTable.getCellValue(rowIndex, columnIndex);

			// Assert
			double expectedValue = shortColumnOne.getValueForOneSpecifiedRow(rowIndex);
			Assert::AreEqual(expectedValue, actualValue);
		}

	};
}



#include "Baseline.h"
#include "Column.h"
#include "Table.h"

#include <cassert>
#include <iostream>
#include <limits>

using Column = ConsoleAppRansacIINamespace::Core::Column;
using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace Core {
namespace UnitTest {

std::vector<double> shortVectorOne{ 0, 1.1, 2.2 };
Column shortColumnOne{ shortVectorOne, "First vector" };
std::vector<double> shortVectorTwo{ 3.14, 1.414, 2.718 };
Column shortColumnTwo{ shortVectorTwo, "Second vector" };
std::vector<double> longVector{ 0, 0.1, 0.2, 0.3, 0.4 };
Column longColumn{ longVector, "Long Vector" };


int testOfMethodsForEmptyTable() {
	// Arrange
    Table emptyTable{ "Empty table" };

	// Act
	size_t actualNoOfColumns = emptyTable.getNoOfColumns();

	// Assert
	if (0 != actualNoOfColumns) {
		return CTestResult::Failure;
	};

	try {
	    double valueFromEmptyTable = emptyTable.getCellValue(0, 0);
	}
	catch (const Table::ColumnIndexOutOfBounds& columnIndexOutOfBound){
		return CTestResult::Success;
	}
	catch (std::exception& e) {
		return CTestResult::Failure;
	}

	return CTestResult::Success;
}

int testWhenNewColumnIsAddedToEmptyTable() {
	// Arrange
	Table emptyTable{ "Empty table" };

	// Act
	emptyTable.appendColumn(shortColumnOne);

	// Assert
	if (1 != emptyTable.getNoOfColumns()) {
		return CTestResult::Failure;
	}

	for (size_t index = 0; index < shortVectorOne.size() ; index++) {
		if (!(std::fabs(shortVectorOne.at(index) - emptyTable.getCellValue(index, 0))<epsilon)) {
			return CTestResult::Failure;
		}
	}
	return CTestResult::Success;
}

int testAddTwoColumnsOfSameLength() {
	// Arrange
	Table testTable{ "Test Table" };

	// Act
	testTable.appendColumn(shortColumnOne);
	testTable.appendColumn(shortColumnTwo);

	// Assert
	size_t actualNoOfColumns = testTable.getNoOfColumns();
	if (2 != actualNoOfColumns) {
		return CTestResult::Failure;
	};

	for (size_t columnIndex = 0; columnIndex < actualNoOfColumns; columnIndex++) {
		Column currentColumn = testTable.getColumn(columnIndex);
		size_t currentNoOfRows = currentColumn.getNoRows();
		for (size_t rowIndex = 0; rowIndex < currentNoOfRows; rowIndex++) {
			double actualValue = currentColumn.getValueForOneSpecifiedRow(rowIndex);
			double expectedValue = columnIndex == 0 ? shortVectorOne.at(rowIndex) : shortVectorTwo.at(rowIndex);
			if (!(std::fabs(expectedValue - actualValue) < epsilon)) {
				return CTestResult::Failure;
			}
		};
	};

	return CTestResult::Success;
}

int testAddColumnLongerThanTableColumns() {
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

	if (isColumnAsExpected) {
	    return CTestResult::Success;
	}
	else {
		return CTestResult::Failure;
	}
}

int testAddColumnShorterThanTableColumns() {
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

	if (isColumnAsExpected) {
		return CTestResult::Success;
	}
	else {
		return CTestResult::Failure;
	}
}

int testOfGetNoOfColumns() {
	// Arrange
	Table testTable{ "Test Table" };
	testTable.appendColumn(shortColumnOne);
	testTable.appendColumn(shortColumnTwo);
	constexpr size_t expectedNoOfColumns = 2;

	// Act
	size_t actualNoOfColumns = testTable.getNoOfColumns();

	// Assert
	if (expectedNoOfColumns != actualNoOfColumns) {
		return CTestResult::Failure;
	}
	else {
		return CTestResult::Success;
	}
}

int testGetColumnOfSpecifiedIndex() {
	// Arrange
	Table testTable{ "Test Table" };

	// Act
	testTable.appendColumn(shortColumnOne);
	testTable.appendColumn(shortColumnTwo);
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

	if (isFirstColumnEqual && isSecondColumnEqual) {
	    return CTestResult::Success;
	}
	else {
		return CTestResult::Failure;
	}
}

int testGetCellValueFromTable() {
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
	if (std::fabs(expectedValue - actualValue) < epsilon) {
		return CTestResult::Success;
	}
	else {
		return CTestResult::Failure;
	}
}

} // namespace UnitTest
} // namespace Core
} // namespace ConsoleAppRansacIINamespace

int main() {
	using namespace ConsoleAppRansacIINamespace::Core::UnitTest;

	bool overallResult = 
		testOfMethodsForEmptyTable() ||
		testWhenNewColumnIsAddedToEmptyTable() ||
		testAddTwoColumnsOfSameLength() ||
		testAddColumnShorterThanTableColumns() ||
		testAddColumnLongerThanTableColumns() ||
		testOfGetNoOfColumns() ||
		testGetColumnOfSpecifiedIndex() ||
		testGetCellValueFromTable();
	return overallResult;
}


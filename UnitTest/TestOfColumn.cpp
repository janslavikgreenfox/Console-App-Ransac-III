#include "Baseline.h"
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
			size_t actualNoOfColumns = emptyColumn.getNoRows();
			std::string emptyColumnHeader = emptyColumn.getHeader();
			std::vector<double> emptyColumnValues = emptyColumn.getValuesForAllRows();
			double averageOfEmptyColumn = emptyColumn.getAverage();

			// Assert
			//CTestResult cTestResult{ CTestResult::Failure };
			constexpr size_t expectedNoOfRows = 0;
			//if (actualNoOfColumns != expectedNoOfRows) {
			//	return CTestResult::Failure;
			//}
			Assert::AreEqual(actualNoOfColumns, expectedNoOfRows);
			// 
			//if (emptyColumnName != emptyColumnHeader) {
			//	return CTestResult::Failure;
			//}
			Assert::AreEqual(emptyColumnName, emptyColumnHeader);
			//if (!emptyColumnValues.empty()) {
			//	return CTestResult::Failure;
			//}
			constexpr double expectedMeanOfEmptyColumn = 0;
			//if (expectedMeanOfEmptyColumn != averageOfEmptyColumn) {
			//	return CTestResult::Failure;
			//}
			Assert::AreEqual(expectedMeanOfEmptyColumn, averageOfEmptyColumn);

			//try {
			//	double oneValueFromEmptyColumn = emptyColumn.getValueForOneSpecifiedRow(0);
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
			//		= emptyColumn.getValuesForSpecifiedRows(std::vector<size_t>{0, 1});
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
			size_t actualNoOfColumns = column.getNoRows();
			std::string actualColumnName = column.getHeader();
			double secondItem = column.getValueForOneSpecifiedRow(1);
			std::vector<double> allRows = column.getValuesForAllRows();
			double average = column.getAverage();
			
			// Assert
			size_t expectedNoOfRows = input.size();
			Assert::AreEqual(actualNoOfColumns, expectedNoOfRows);
			//if (actualNoOfColumns != expectedNoOfRows) {
			//	return CTestResult::Failure;
			//}
			
			Assert::AreEqual(actualColumnName, inputColumnName);
			//if (actualColumnName != inputColumnName) {
			//	return CTestResult::Failure;
			//}
			
			Assert::AreEqual(secondItem, input.at(1));
			//if (secondItem != input.at(1)) {
			//	return CTestResult::Failure;
			//}
			
			//Assert::AreEqual(allRows, input);
			//if (allRows != input) {
			//	return CTestResult::Failure;
			//}
			
			double expectedSum{0};
			std::for_each(input.begin(), input.end(), [&expectedSum](double& item) {expectedSum += item; });
			Assert::AreEqual(average, expectedSum / expectedNoOfRows);
			//if (average != expectedSum / expectedNoOfRows) {
			//	return CTestResult::Failure;
			//}
			
			//return CTestResult::Success;
		}
	};
}


//int testGetNoRowsForSimpleColumn() {
//	// Arrange
//	std::cout << "testGetNoRowsForSimpleColumn()" << std::endl;
//	std::vector<double> input = { 0, 1, 2 };
//	std::string inputColumnName{ "Column test No. 1" };
//	Column column{ input, inputColumnName };
//
//	// Act 
//	size_t actualNoOfColumns = column.getNoRows();
//	std::string actualColumnName = column.getHeader();
//	double secondItem = column.getValueForOneSpecifiedRow(1);
//	std::vector<double> allRows = column.getValuesForAllRows();
//	double average = column.getAverage();
//	//std::vector<double>
//
//	// Assert
//	size_t expectedNoOfRows = input.size();
//	if (actualNoOfColumns != expectedNoOfRows) {
//		return CTestResult::Failure;
//	}
//
//	if (actualColumnName != inputColumnName) {
//		return CTestResult::Failure;
//	}
//
//	if (secondItem != input.at(1)) {
//		return CTestResult::Failure;
//	}
//
//	if (allRows != input) {
//		return CTestResult::Failure;
//	}
//
//	double expectedSum{0};
//	std::for_each(input.begin(), input.end(), [&expectedSum](double& item) {expectedSum += item; });
//	if (average != expectedSum / expectedNoOfRows) {
//		return CTestResult::Failure;
//	}
//
//	return CTestResult::Success;
//}
//
//} // namespace UnitTest
//} // namespace Core
//} // namespace ConsoleAppRansacIINamespace
//
//int main() {
//	using namespace ConsoleAppRansacIINamespace::Core::UnitTest;
//
//	bool overallResult =
//		testForEmptyColumn() ||   // check the empty column use case
//		testGetNoRowsForSimpleColumn();    // check the simple column use case
//		//testGetNoRowsForExtremeLengthColumn(); 
//	return overallResult;
//}
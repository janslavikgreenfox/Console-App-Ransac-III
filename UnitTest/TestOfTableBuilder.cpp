#include "Baseline.h"
#include "Column.h"
#include "Table.h"
#include "TableBuilder.h"

#include <fstream>
#include <array>

using CsvTableBuilder = ConsoleAppRansacIINamespace::IO::CsvTableBuilder;

namespace ConsoleAppRansacIINamespace {
namespace Core {
namespace UnitTest {

int testOfSimpleTableFromCSVFile() {
	// Arrange
	std::string simpleTableTestCSVFileName = "simpleTableTest.csv";
	const char delimiter = ',';

	std::ofstream simpleTableTestCSVFile{ simpleTableTestCSVFileName };

	constexpr size_t NoOfHeaderRows = 1U;
	constexpr const char* TableName = "Test Table";
	simpleTableTestCSVFile << TableName << "\n";

	constexpr const char* Header1 = "Header1";
	simpleTableTestCSVFile << Header1 << delimiter <<"\n";
	constexpr const std::array<double, 3U> simpleColumn = { 1.2, 2.3, 3.4 };
	for (const double& value : simpleColumn) {
		simpleTableTestCSVFile << value << delimiter << "\n";
	}

	simpleTableTestCSVFile.close();


	// Act
	CsvTableBuilder csvTableBuilder{ simpleTableTestCSVFileName, NoOfHeaderRows};
	csvTableBuilder.buildTable();
	
	// Assert
	std::unique_ptr<Table> table = csvTableBuilder.getTable();
	
	size_t actualNoOfColumns = table->getNoOfColumns();
	size_t expectedNoOfColumns = 1;
	if (expectedNoOfColumns != actualNoOfColumns) {
		return CTestResult::Failure;
	}

	std::string actualTableName = table->getName();
	std::string expectedTableName = "Test Table";
	if (expectedTableName != actualTableName) {
		return CTestResult::Failure;
	}

	Column actualColumn = table->getColumn(0);
	size_t actualNoOfRows = actualColumn.getNoRows();
	size_t expectedNoOfRows = 3;
	if (expectedNoOfRows != actualNoOfRows) {
		return CTestResult::Failure;
	}

	std::vector<double> actualColumnValues = actualColumn.getValuesForAllRows();
	for (size_t index = 0; index < actualNoOfRows; index++) {
		if ( simpleColumn.at(index) != actualColumnValues.at(index)) {
			return CTestResult::Failure;
		}
	}
	return CTestResult::Success;
}

} // namespace UnitTest
} // namespace Core
} // namespace ConsoleAppRansacIINamespace

int main() {
	using namespace ConsoleAppRansacIINamespace::Core::UnitTest;

	bool overallResult =
		testOfSimpleTableFromCSVFile();
	return overallResult;
}
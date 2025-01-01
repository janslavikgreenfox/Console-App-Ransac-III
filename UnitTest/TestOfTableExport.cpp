#include "Table.h"
#include "Column.h"
#include "TableExport.h"
#include "Baseline.h"
#include "CppUnitTest.h"

using Column = ConsoleAppRansacIINamespace::Core::Column;
using Table = ConsoleAppRansacIINamespace::Core::Table;
using TableExport = ConsoleAppRansacIINamespace::IO::TableExport;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{

std::vector<double> shortVectorOne{ 0, 1.1, 2.2 };
Column shortColumnOne{ shortVectorOne, "First vector" };
std::vector<double> shortVectorTwo{ 3.14, 1.414, 2.718 };
Column shortColumnTwo{ shortVectorTwo, "Second vector" };
	
    TEST_CLASS(TableExportTest) {
    public:

	    TEST_METHOD(SimpleTableExport) {
			// Arrange
			Table testTable{ "Test Table" };
			testTable.appendColumn(shortColumnOne);
			testTable.appendColumn(shortColumnTwo);
			std::string expectedResult =
				"Test Table\n"
				"First vector,Second vector,\n"
				"0.000000,3.140000,\n"
				"1.100000,1.414000,\n"
				"2.200000,2.718000,\n";

			// Act
			TableExport tableExport{};
			std::string actualResult = tableExport.ExportToCsvString(testTable);

			// Assert
			Assert::AreEqual(expectedResult, actualResult);
	    }
	};
}


//int testSimpleTableExported() {
//	// Arrange
//	Table testTable{ "Test Table" };
//	testTable.appendColumn(shortColumnOne);
//	testTable.appendColumn(shortColumnTwo);
//	std::string expectedResult = 
//		"Test Table\n"
//		"First vector,Second vector,\n"
//		"0.000000,3.140000,\n"
//		"1.100000,1.414000,\n"
//		"2.200000,2.718000,\n";
//
//	// Act
//	TableExport tableExport{};
//	std::string actualResult = tableExport.ExportToCsvString(testTable);
//
//	// Assert
//
//	if (actualResult == expectedResult) {
//		return CTestResult::Success;
//	}
//	else {
//		return CTestResult::Failure;
//	}
//}
//
//} // namespace Core
//} // namespace ConsoleAppRansacIINamespace
//} // namespace UnitTests
//
//int main() {
//	using namespace ConsoleAppRansacIINamespace::Core::UnitTest;
//
//	bool overallResult = 
//		testSimpleTableExported();
//	return overallResult;
//}
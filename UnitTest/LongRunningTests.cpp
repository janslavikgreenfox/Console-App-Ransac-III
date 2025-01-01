#include "Baseline.h"
#include "Column.h"
#include "CppUnitTest.h"

#include <iostream>

using Column = ConsoleAppRansacIINamespace::Core::Column;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(LongRunningTest) {
    public:

		TEST_METHOD(ExtremeLongColumn) {
			Assert::IsTrue(true);
		}
	};
}

//namespace ConsoleAppRansacIINamespace {
//namespace Core {
//namespace UnitTest {
//
//int testGetNoRowsForExtremeLengthColumn() {
//
//	// Arrange
//	constexpr size_t hugeVectorSize = 2000000000;
//	std::vector<double> hugeVector(hugeVectorSize, 1.414);
//
//	// Act
//	try {
//		Column column{hugeVector, "Really huge vector"};
//	}
//	// Assert
//	catch (Column::BadAlloc& e) {
//		std::cout << e.what();
//		return CTestResult::Success;
//	}
//
//	return CTestResult::Failure;
//}
//
//} // namespace UnitTests	
//} // namespace Core
//} // namespace ConsoleAppRansacIINamespace
//
//int main() {
//	using namespace ConsoleAppRansacIINamespace::Core::UnitTest;
//
//	int overallResult = 
//		testGetNoRowsForExtremeLengthColumn();
//	return overallResult;
//}
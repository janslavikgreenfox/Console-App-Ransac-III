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

#include "Table.h"
#include "Column.h"
#include "TableExport.h"
#include "Common.h"
#include <gtest/gtest.h>

using Column = ConsoleAppRansacIINamespace::Core::Column;
using Table = ConsoleAppRansacIINamespace::Core::Table;
using TableExport = ConsoleAppRansacIINamespace::IO::TableExport;

namespace {
	std::vector<double> shortVectorOne{ 0, 1.1, 2.2 };
	Column shortColumnOne{ shortVectorOne, "First vector" };
	std::vector<double> shortVectorTwo{ 3.14, 1.414, 2.718 };
	Column shortColumnTwo{ shortVectorTwo, "Second vector" };
}

TEST(TableExportTest, SimpleTableExport)
{
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
	EXPECT_EQ(expectedResult, actualResult);
}
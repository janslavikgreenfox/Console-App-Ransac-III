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
#include "TableBuilder.h"
#include <gtest/gtest.h>
#include <fstream>
#include <array>

using CsvTableBuilder = ConsoleAppRansacIINamespace::IO::CsvTableBuilder;
using Column = ConsoleAppRansacIINamespace::Core::Column;
using Table = ConsoleAppRansacIINamespace::Core::Table;

TEST(TableBuilderTest, SimpleTableFromCSVFile)
{
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
	EXPECT_EQ(expectedNoOfColumns, actualNoOfColumns);

	std::string actualTableName = table->getName();
	std::string expectedTableName = "Test Table";
	EXPECT_EQ(expectedTableName, actualTableName);

	Column actualColumn = table->getColumn(0);
	size_t actualNoOfRows = actualColumn.getNoOfRows();
	size_t expectedNoOfRows = 3;
	EXPECT_EQ(expectedNoOfRows, actualNoOfRows);

	std::vector<double> actualColumnValues = actualColumn.getAllRows();
	for (size_t index = 0; index < actualNoOfRows; index++) {
		EXPECT_EQ(simpleColumn.at(index), actualColumnValues.at(index));
	}
}


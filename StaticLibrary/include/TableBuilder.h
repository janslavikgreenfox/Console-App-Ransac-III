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

#pragma once

#include "Table.h"
#include <vector>
#include <string>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

/**
* @class ITableBuilder
* @brief An interface for a table builder.
*/
class ITableBuilder {
  public:
	/**
	* @brief Builds a table.
	*/
	virtual void buildTable() = 0;

	/**
	* @brief Gets the table.
	*/
	virtual std::unique_ptr<Table> getTable() = 0;
};

/**
* @class CsvTableBuilder
* @brief A class that builds a table from a CSV file.
*/
class CsvTableBuilder : public ITableBuilder {
  public:
	/**
	* @brief Constructor for the CsvTableBuilder class.
	* @param csvFilename The name of the CSV file.
	* @param hdLines The number of header lines in the CSV file.
	*/
	  CsvTableBuilder(std::string csvFilename = "", int hdLines = 0);
		 // : _csvFilename{ csvFilename }, _hdLines{ hdLines };

	/**
	* @brief Builds a table.
	*/
	virtual void buildTable() override;

	/**
	* @brief Gets the table.
	* @return The table that is builded by the build method.
	*/
	std::unique_ptr<Table> getTable() override;

  private:
	/**
	* @brief The csv file name.
	*/
	std::string	_csvFilename;

	/**
	* @brief The created table.
	*/
	std::unique_ptr<Table>	_currentTable;

	/**
	* @brief The number of header lines in the CSV file.
 	*/
	int _hdLines;
};

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
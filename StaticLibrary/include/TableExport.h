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
#include <string>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

/**
* @class ITableExport interface
*/
class ITableExport {
public:
	/**
	* @brief Exports a table somehow.
	*/
	virtual void exportTable() const = 0;

	/**
	* @brief Gets the string that represents the exported table.
	* @return The string that represents the exported table.
	*/
	virtual std::string getExportedString() const = 0;

	/**
	* @brief Destructor
	*
	* @note If a class has at least one virtual method, it should also have a virtual destructor.
	*/
	virtual ~ITableExport() = default;
};

/**
* @class TableExportToString
*/
class TableExportToCsvBase : public ITableExport {
  public:
	/**
	* @brief Constructor for the TableExportToString class.
	* @param ptrTable The pointer to a table to export.
	* @param delimiter The delimiter character.
	*/
	  TableExportToCsvBase(std::shared_ptr<Table> ptrTable, char delimiter = ',')
		  : _pTable{ ptrTable }, _delimiter{delimiter}
	  {
		  generateCsvString();
	  };

	/**
	* @brief Exports a table to a CSV string.
	*/
	virtual void exportTable() const override;

	/**
	* @brief Gets the CSV string.
	*/
	std::string getExportedString() const override { 
		return _csvString; 
	}

  protected:

  private:
	/**
	* @brief Generates a CSV string.
	* 
	*/
	void generateCsvString();

   /**
   * @brief The table to export.
   */
   std::shared_ptr<Table> _pTable;
   
   /**
   * @brief The delimiter character.
   */
   char _delimiter;

   /**
   * @brief The CSV string.
   */
   std::string _csvString;
};

/**
* @class TableExportToCsvFile
*/
//class TableExportToCsvFile : public TableExportToCsvBase {
class TableExportToCsvFile : public ITableExport {

  public:
	/**
	* @brief Constructor for the TableExportToCsvFile class.
	* @param table The table to export.
	* @param fileName The name of the CSV file.
	* @param delimiter The delimiter character.
	*/
	TableExportToCsvFile(
		std::shared_ptr<Table> ptrTable, const std::string& fileName, char delimiter)
		  : _pTable { ptrTable }, 
		    _fileName{ fileName },
		    _delimiter{ delimiter }
    {
		_pTableExportToCsvBase = std::make_unique<TableExportToCsvBase>( ptrTable, delimiter );
	};

	/**
	* @brief Exports a table to a CSV file.
	*/
	virtual void exportTable() const override;

	/**
	* @brief Gets the CSV string.
	*/
	std::string getExportedString() const override { 
		std::string exportedString = _pTableExportToCsvBase->getExportedString(); 
		return exportedString;
	};

private:
	/**
	* @brief The table to export.
	*/
	std::shared_ptr<Table> _pTable;

	/**
	* @brief The name of the CSV file.
	*/
	const std::string _fileName;

	/**
	* @brief The delimiter character.
	*/
	char _delimiter;

	/**
	* @brief The table export to CSV string.
	*/
	std::unique_ptr<TableExportToCsvBase> _pTableExportToCsvBase;
};

/**
* @class TableExportToFile
*/

/**
* @class TableExport
* @brief A class that exports a table to a CSV file or string.
*/
class TableExport {
  public:
    /**
	* @brief Exports a table to a CSV string.
	* @param table The table to export.
	* @param delimiter The delimiter character.
    */
    std::string ExportToCsvString(const Table& table, const char delimiter = ',') const;

    /**
	* @brief Exports a table to a CSV file.
	* @param table The table to export.
	* @param fileName The name of the CSV file.
	* @param delimiter The delimiter character.
    */
    void ExportToCsvFile(const Table& table, const std::string fileName, const char delimiter) const;
};

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
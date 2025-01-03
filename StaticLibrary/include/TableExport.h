#pragma once

#include "Table.h"
#include <string>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

/**
* @class TableExport
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
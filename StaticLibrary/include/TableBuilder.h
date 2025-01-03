#pragma once

#include "Table.h"
#include <vector>
#include <string>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

/**
* @class TableBuilder
* @brief An interface for a table builder.
*/
class TableBuilder {
  public:
	/**
	* @brief Builds a table.
	*/
	virtual void buildTable() = 0;

	/**
	* @brief Gets the table.
	*/
	virtual std::unique_ptr<Table> getTable() = 0;

  protected:
	/**
	* @brief Constructor for the TableBuilder class.
	*/
	TableBuilder() {};
  private:
};


class CsvTableBuilder : public TableBuilder {
  public:
	/**
	* @brief Constructor for the CsvTableBuilder class.
	* @param csvFilename The name of the CSV file.
	* @param hdLines The number of header lines in the CSV file.
	*/
	CsvTableBuilder(std::string csvFilename = "", int hdLines = 0);

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
};

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
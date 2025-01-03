#pragma once

#include "Table.h"
#include "TableExport.h"
#include "TableBuilder.h"

using Table = ConsoleAppRansacIINamespace::Core::Table;
using Column = ConsoleAppRansacIINamespace::Core::Column;

namespace ConsoleAppRansacIINamespace {
namespace IO {

/**
* @class TableFacade
* @brief A facade for a table.
* 
* This class is a facade for a table. It provides a simple interface to the table.
* 
*/
class TableFacade {
public:
	/**
	* @brief Constructor for the TableFacade class.
	* @param tableName The name of the table.
	*/
	TableFacade(std::string& tableName) : _table{ tableName }, _tableExport{} {
	};

	/**
	* @brief Copy constructor
	* @param other The other table facade to be copied.
	*/
	TableFacade(const TableFacade& other) = default;

	/**
	* @brief Move constructor
	* @param other The other table facade to be moved.
	*/
	TableFacade(TableFacade&& other) = default;

	/**
	* @brief Copy assignment operator
	* @param other The other table facade to be copied.
	*/
	TableFacade& operator=(const TableFacade& other) = default;

	/**
	* @brief Move assignment operator
	* @param other The other table facade to be moved.
	*/
	TableFacade& operator=(TableFacade&& other) = default;

	/**
	* @brief Destructor for the TableFacade class.
	*/
	~TableFacade() = default;

	/**
	* @brief Get the name of the table.
	* @return The name of the table.
	*/
	size_t getNoOfColumns() const {
		return _table.getNoOfColumns();
	}

	/**
	* @brief Get the common number of rows in all columns.
	* @return The common number of rows in all columns.
	*/
	size_t getCommonNoOfRows() const {
		return _table.getCommonNoOfRows();
	}

	/**
	* @brief Add a column to the table.
	* @param column The column to be added.
	*/
	void appendColumn(const Column& column) {
		_table.appendColumn(column);
	}

	/**
	* @brief Get a column from the table.
	* @param columnIndex The index of the column in the table.
	* @return The column at the specified index.
	*/
	Column getColumn(size_t columnIndex) const {
		return _table.getColumn(columnIndex);
	}

	/**
	* @brief Get the value at a specified cell in the table.
	* @param cellRowIndex The row index of the cell.
	* @param cellColumnIndex The column index of the cell.
	* @return The value at the specified cell of the table.
	*/
	double getCellValue(size_t cellRowIndex, size_t cellColumnIndex) const {
		return _table.getCellValue(cellRowIndex, cellColumnIndex);
	}

	/**
	* @brief Export the table to a CSV string.
	* @param delimiter The delimiter character.
	* @return The table as a CSV string.
	*/
	void exportTableToCsvFile(const std::string& fileName, const char delimiter = ',') const {
		_tableExport.ExportToCsvFile(_table, fileName, delimiter);
	}

  private:
	  /**
	  * @brief The table.
	  */
	  Table _table;

	  /**
	  * @brief The table export.
	  */
	  TableExport _tableExport;

	  //TableBuilder _tableBuilder;
};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
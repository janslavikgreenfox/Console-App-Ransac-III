#pragma once

#include "Column.h"
#include <iostream>
#include <string>

namespace ConsoleAppRansacIINamespace {
namespace Core {

/**
* @class Table
* @brief A class that represents a table of data.
* A table is a collection of columns.
* Each column is a collection of cells.
* Each cell is a value.
* 
* Features:
* - Add a column to the table.
* - Get the number of columns in the table.
* - Get the name of the table.
* - Get the common number of rows in all columns.
* - Get a column from the table.
* - Get a cell value from the table.
* - Output the table to an output stream.
* - Exception handling for out of bounds column indexes.
* - Exception handling for bad memory allocation.
* 
*/
class Table {
  public:
	/**
	* @brief Constructor for the Table class.
	* @param name The name of the table.
	* @param noOfColumns The number of columns in the table.
	*/
	Table(std::string name="") : _name(name), _noOfColumns(0) {};

	/**
	* @brief Copy constructor
	* @param other The other table to be copied.
	*/
	Table(const Table& other) = default;

	/**
	* @brief Move constructor
	* @param other The other table to be moved.
	*/
	Table(Table&& other) = default;

	/**
	* @brief Copy assignment operator
	* @param other The other table to be copied.
	*/
	Table& operator=(const Table& other) = default;

	/**
	* @brief Move assignment operator
	* @param other The other table to be moved.
	*/
	Table& operator=(Table&& other) = default;

	/**
	* @brief Destructor
	*/
	~Table() = default;

	/**
	* @brief Get name of the table.
	* @return The name of the table.
	*/
	std::string getName() const { return _name; }

	/**
	* @brief Get the number of columns in the table.
	* @return The number of columns in the table.
	*/
	size_t getNoOfColumns() const { return _noOfColumns; }

	/**
	* @brief Get the common number of rows in all columns.
	* @return The common number of rows in all columns.
	*/
	size_t getCommonNoOfRows() const;

	/**
	* @brief Add a column to the table.
	* @param column The column to be added to the table.
	*/
	void appendColumn(const Column & column);

	/**
	* @brief Get the column of the specified index from the table.
	* @param index The index of the column to get.
	* @return The column of the specified index.
	*/
	Column getColumn(size_t index) const;

	/**
	* @brief Get the value of the cell at the specified row and column indexes.
	* @param cellRowIndex The row index of the cell.
	* @param cellColumnIndex The column index of the cell.
	* @return The value of the cell at the specified row and column indexes.
	*/
	double getCellValue(size_t cellRowIndex, size_t cellColumnIndex) const;
	
	/**
	* @brief Output the table to an output stream.
	* @param os The output stream to output the table to.
	* @param table The table to output to the output stream.
	*/
	friend std::ostream& operator<<(std::ostream& os, const Table& table);

	//std::string ExportToCsvString(const char delimiter);

	//void ExportToCsvFile(const std::string fileName, const char delimiter);

	/**
	* @brief Exception class for out of bounds column indexes.
	*/
	class ColumnIndexOutOfBounds : public std::exception {
		private:
			std::string _message;
		public:
			/**
			* @brief Constructor for the ColumnIndexOutOfBounds exception.
			* @param badColumnIndex The bad column index.
			* @param maxNoOfColumns The maximum number of columns.
			*/
			ColumnIndexOutOfBounds(size_t badColumnIndex, size_t maxNoOfColumns) : exception() {
				_message = "The column index \"" + std::to_string(badColumnIndex + 1) + "\" out of the table "
					"column index bounds, i.e. from 1 to " + std::to_string(maxNoOfColumns) + ".";
			};
			/**
			* @brief Get the message of the exception.
			* @return The message of the exception.
			*/
			const char* what() const noexcept override {
				return _message.c_str();
			};
	};

  private:
	/**
	* @brief The vector of columns in the table.
	*/
	std::vector<Column> _tableColumns;

	/**
	* @brief The name of the table.
	*/
	std::string _name;

	/**
	* @brief The number of columns in the table.
	*/
	size_t _noOfColumns;
};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace

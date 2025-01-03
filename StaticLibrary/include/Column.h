#pragma once

#include "Baseline.h"
#include <vector>
#include <string>
#include <stdexcept>

namespace columnUtils {
	std::vector<size_t> getRandomIndexes(size_t numberOfSelectedPoints, size_t noOfRows);
}

namespace ConsoleAppRansacIINamespace {
namespace Core {

/**
* @class Column
* @brief A class to represent a column of values.
* 
* The 'Column' class provides a way to store a column of values.
* Each column has a header (string) and a vector of values (doubles).
* 
* Features:
* - Add a row to the column.
* - Get the number of rows in the column.
* - Get the header of the column.
* - Get all the values in the column.
* - Get the value at a specified row index.
* - Get the values at specified row indexes.
* - Get the average of the values in the column.
* - Output the column to an output stream.
* - Exception handling for out of bounds row indexes.
* - Exception handling for bad memory allocation.
*
*/
class Column 
{  
  public:
	/**
	* @brief Constructor for the Column class.
	* @param rowVector A vector of values to be stored in the column.
	* @param header The header of the column.
	*/
	Column(const std::vector<double>& rowVector, const std::string header); 

	/**
	* @brief Copy constructor
	* @param other The other column to be copied.
	*/
	Column(const Column& other) = default;

	/**
	* @brief Move constructor
	* @param other The other column to be moved.
	*/
	Column(Column&& other) = default;

	/**
	* @brief Copy assignment operator
	* @param other The other column to be copied.
	*/
	Column& operator=(const Column& other) = default;

	/**
	* @brief Move assignment operator
	* @param other The other column to be moved.
	*/
	Column& operator=(Column&& other) = default;

	/**
	* @brief Destructor
	*/
	~Column() = default;

	/**
	* @brief Add a row to the column values
	* @param value The double value to be added as a new row
	*/
	void addRow(const double value);

	/**
	* @brief Get number of rows in the column
	*/
	size_t getNoRows() const;

	/**
	* @brief Get the column header
	* @return The header of the column
	*/
	std::string getHeader() const;

	/**
	* @brief Get all rows from the Column
	* @return A vector of all the values in the column
	*/
	std::vector<double> getValuesForAllRows() const;

	/**
	* @brief Get the value at a specified row index
	* @param specifiedRowIndex The index of the row to get the value from
	* @return The value at the specified row index
	*/
	double getValueForOneSpecifiedRow(const size_t& specifiedRowIndex) const;

	/**
	* @brief Get the values at specified row indexes
	* @param specifiedRowIndexes A vector of picked indexes of the rows to get the values from
	* @return A vector of the values at the specified row indexed
	*/
	Column getValuesForSpecifiedRows(const std::vector<size_t>& specifiedRowIndexes) const;

	/**
	* @brief Get the average of the values in the column
	* @return The average of the values in the column
	*/
	double getAverage() const;

	/**
	* @brief Output the column to an output stream
	* @param os The output stream to output the column to
	* @param column The column to output
	* @return The output stream
	*/
	friend std::ostream& operator<<(std::ostream& os, const Column& column);

	/**
	* @class RowIndexOutOfBounds
	* @brief Exception for when the row index is out of bounds
	*/
	class RowIndexOutOfBounds : public std::runtime_error {
		public:
			explicit RowIndexOutOfBounds(std::string& message) noexcept
				: std::runtime_error(message) {}
	};

	/**
	* @class BadAlloc
	* @brief Exception for when memory allocation fails
	*/
	class BadAlloc : public std::bad_alloc {
	    private:
		    std::string message;

	    public:
		    explicit BadAlloc(std::string& msg) noexcept : message{ msg } {}

		    const char* what() const noexcept override {
			    return message.c_str();
		    }
	};

  private:
	/**
	* @brief The vector of values in the column
	*/
	std::vector<double> _colValues;
	
	/**
	* @brief The number of rows in the column
	*/
	size_t _noRows;

	/**
	* @brief The header of the column
	*/
	std::string _colHeader;

	/**
	* @brief Get the values at selected indexes
	* @param selectedIndexes The indexes of the rows to get the values from
	* @return A vector of the values at the selected indexes
	*/
	std::vector<double> getValuesAtSelectedIndexes(const std::vector<size_t>& selectedIndexes) const;

	/**
	* @brief Get the message that contains index and column header
	*/
	std::string getIndexAndColumnNameMessage(const size_t& index) const;
};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
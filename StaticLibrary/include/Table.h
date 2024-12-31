#pragma once

#include "Column.h"
#include <iostream>
#include <string>

namespace ConsoleAppRansacIINamespace {
namespace Core {

class Table {

  public:
	Table(std::string name="") : _name(name), _noOfColumns(0) {};

	Table(const Table& other) = default;

	Table(Table&& other) = default;

	Table& operator=(const Table& other) = default;

	Table& operator=(Table&& other) = default;

	~Table() = default;

	std::string getName() const { return _name; }

	size_t getNoOfColumns() const { return _noOfColumns; }

	size_t getCommonNoOfRows() const;

	void appendColumn(const Column & column);

	Column getColumn(size_t index) const;

	double getCellValue(size_t cellRowIndex, size_t cellColumnIndex) const;
	
	friend std::ostream& operator<<(std::ostream& os, const Table& table);

	//std::string ExportToCsvString(const char delimiter);

	//void ExportToCsvFile(const std::string fileName, const char delimiter);

	class ColumnIndexOutOfBounds : public std::exception {
		private:
			std::string _message;
		public:
			ColumnIndexOutOfBounds(size_t badColumnIndex, size_t maxNoOfColumns) : exception() {
				_message = "The column index \"" + std::to_string(badColumnIndex + 1) + "\" out of the table "
					"column index bounds, i.e. from 1 to " + std::to_string(maxNoOfColumns) + ".";
			};
			const char* what() const noexcept override {
				return _message.c_str();
			};
	};

  private:
	std::vector<Column> _tableColumns;
	std::string _name;
	size_t _noOfColumns;
};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace

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

class Column 
{  
  public:
	Column(const std::vector<double>& rowVector, const std::string header); 

	Column(const Column& other) = default;

	Column(Column&& other) = default;

	Column& operator=(const Column& other) = default;

	Column& operator=(Column&& other) = default;


	void addRow(const double value);

	size_t getNoRows() const;
	std::string getHeader() const;
	std::vector<double> getValuesForAllRows() const;
	double getValueForOneSpecifiedRow(const size_t& specifiedRowIndex) const;
	Column getValuesForSpecifiedRows(const std::vector<size_t>& specifiedRowIndexes) const;
	double getAverage() const;

	friend std::ostream& operator<<(std::ostream& os, const Column& column);

	class RowIndexOutOfBounds : public std::runtime_error {
		public:
			explicit RowIndexOutOfBounds(std::string& message) noexcept
				: std::runtime_error(message) {}
	};

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
	std::vector<double> _colValues;
	size_t _noRows;
	std::string _colHeader;

	std::vector<double> getValuesAtSelectedIndexes(const std::vector<size_t>& selectedIndexes) const;

	std::string getIndexAndColumnNameMessage(const size_t& index) const;
};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
#include <vector>
#include<string>
#include<iostream>
#include<fstream>

#include "Table.h"

namespace ConsoleAppRansacIINamespace {
namespace Core {

size_t Table::getCommonNoOfRows() const {
	size_t result{ 0 };
	for (auto& item : _tableColumns) {
		size_t itemNoOfRows = item.getNoRows();
		if (itemNoOfRows > result) {
			result = itemNoOfRows;
		}
	}
	return result;
}

constexpr double defaultValueToFillEmptyRow = 0.0;
void Table::appendColumn(const Column& column) {
	Column columnToBeAdded = column;
	if (_noOfColumns != 0) {
		size_t noOfCommonRows = getCommonNoOfRows();
		size_t newColumnNoOfRows = column.getNoRows();
		if (noOfCommonRows > newColumnNoOfRows) {
			for (size_t index = newColumnNoOfRows; index < noOfCommonRows; index++) {
				columnToBeAdded.addRow(defaultValueToFillEmptyRow);
			};
		}
		else {
			if (noOfCommonRows < newColumnNoOfRows) {
				// enlarge the existing columns in the table by extra zeros
				size_t noOfColumns = getNoOfColumns();
				for (Column& columnElementInTable : _tableColumns) {
					for (size_t index = noOfCommonRows; index < newColumnNoOfRows; index++) {
						columnElementInTable.addRow(defaultValueToFillEmptyRow);
					};
				};
			}
		}
	}
	_tableColumns.push_back(columnToBeAdded);
	_noOfColumns++;
}

std::ostream& operator<<(std::ostream& os, const Table& table) {
	for (size_t columnIndex = 0; columnIndex < table.getNoOfColumns(); columnIndex++) {
		os << table.getColumn(columnIndex);
	};
	return os;
}

Column Table::getColumn(size_t columnIndex) const {
	if ( (columnIndex < 0) || (columnIndex > (_noOfColumns - 1)) )
	{
		throw ColumnIndexOutOfBounds(columnIndex, _noOfColumns); 
	}
	return _tableColumns.at(columnIndex);
}

double Table::getCellValue(size_t cellRowIndex, size_t cellColumnIndex) const {
	//TO DO exceptions, out of range
	if (cellColumnIndex + 1 > _noOfColumns) {
		throw ColumnIndexOutOfBounds(cellColumnIndex, _noOfColumns);
	}
	else
	{
		return _tableColumns[cellColumnIndex].getValueForOneSpecifiedRow(cellRowIndex);
	}
}


//std::string Table::ExportToCsvString(const char delimiter = ',') {
//	std::string csvOutput = "";
//	for (size_t columnIndex = 0; columnIndex < _noOfColumns; columnIndex++) {
//		csvOutput += _tableColumns[columnIndex].getHeader() + delimiter;
//	}
//	csvOutput += "\n";
//	size_t currentNumberOfRows = _tableColumns[0].getNoRows();
//	for (size_t rowIndex = 0; rowIndex < currentNumberOfRows; rowIndex++) {
//	    for (size_t columnIndex = 0; columnIndex < _noOfColumns; columnIndex++) {
//			csvOutput += std::to_string(getCellValue(rowIndex,columnIndex)) + delimiter;
//		}
//		csvOutput += "\n";
//	}
//	return csvOutput;
//}
//
//void Table::ExportToCsvFile(std::string fileName="exportTable.csv", const char delimiter=',') {
//	std::ofstream exportFile;
//	exportFile.open(fileName);
//	exportFile << ExportToCsvString(delimiter);
//	exportFile.close();
//}

} // namespace Core
} // namespace ConsoleAppRansacIINamespace

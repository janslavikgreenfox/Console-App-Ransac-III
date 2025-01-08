#include "TableExport.h"

#include <fstream>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

void TableExportToCsvBase::exportTable() const {
}

void TableExportToCsvBase::generateCsvString() {
	// Table name
	_csvString = std::string(" ");
	_csvString = std::string(_pTable->getName() + std::string("\n"));

	// Columns headers
	for (size_t columnIndex = 0; columnIndex < _pTable->getNoOfColumns(); columnIndex++) {
		_csvString += _pTable->getColumn(columnIndex).getHeader() + _delimiter;
	}
	_csvString += "\n";

	// Table data
	size_t currentNumberOfRows = _pTable->getColumn(0).getNoRows();
	size_t currentNumberOfColumns = _pTable->getNoOfColumns();
	for (size_t rowIndex = 0; rowIndex < currentNumberOfRows; rowIndex++) {
		for (size_t columnIndex = 0; columnIndex < currentNumberOfColumns; columnIndex++) {
			_csvString += std::to_string(_pTable->getCellValue(rowIndex, columnIndex)) + _delimiter;
		}
		_csvString += "\n";
	}
}


std::string TableExport::ExportToCsvString(const Table& table, const char delimiter) const {
	
	// Table name
	std::string csvOutput = {table.getName() + std::string("\n")};

	// Columns headers
	for (size_t columnIndex = 0; columnIndex < table.getNoOfColumns(); columnIndex++) {
		csvOutput += table.getColumn(columnIndex).getHeader() + delimiter;
	}
	csvOutput += "\n";

	// Table data
	size_t currentNumberOfRows = table.getColumn(0).getNoRows();
	size_t currentNumberOfColumns = table.getNoOfColumns();
	for (size_t rowIndex = 0; rowIndex < currentNumberOfRows; rowIndex++) {
		for (size_t columnIndex = 0; columnIndex < currentNumberOfColumns; columnIndex++) {
			csvOutput += std::to_string(table.getCellValue(rowIndex, columnIndex)) + delimiter;
		}
		csvOutput += "\n";
	}
	return csvOutput;
}


void TableExportToCsvFile::exportTable() const {
	//generateCsvString();
	//_csvString = getExportedString();
	std::ofstream exportFile;
	exportFile.open(_fileName);
	exportFile << getExportedString(); //_csvString;
	exportFile.close();
}

void TableExport::ExportToCsvFile(const Table& table, std::string fileName = "exportTable.csv", const char delimiter = ',') const {
	std::ofstream exportFile;
	exportFile.open(fileName);
	exportFile << ExportToCsvString(table, delimiter);
	exportFile.close();
}

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
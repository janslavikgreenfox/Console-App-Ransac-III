#include "TableExport.h"

#include <fstream>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

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

void TableExport::ExportToCsvFile(const Table& table, std::string fileName = "exportTable.csv", const char delimiter = ',') const {
	std::ofstream exportFile;
	exportFile.open(fileName);
	exportFile << ExportToCsvString(table, delimiter);
	exportFile.close();
}

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
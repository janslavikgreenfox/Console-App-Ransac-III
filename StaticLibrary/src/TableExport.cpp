// Copyright (C) 2025 Jan Slavik, Blackstone Labs
// 
// This file is part of the Console-App-Ransac-III project.
// 
// Licensed under the MIT License. You may obtain a copy of the License at:
// 
//     https://opensource.org/licenses/MIT
// 
// This software is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "TableExport.h"

#include <fstream>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

void TableExportToCsvBase::exportTable() const {
}

void TableExportToCsvBase::generateCsvString() {
	// Table name
	_csvString = std::string("");
	_csvString = std::string(_pTable->getName() + std::string("\n"));

	// Columns headers
	for (size_t columnIndex = 0; columnIndex < _pTable->getNoOfColumns(); columnIndex++) {
		_csvString += _pTable->getColumn(columnIndex).getHeader() + _delimiter;
	}
	_csvString += "\n";

	// Table data
	size_t currentNumberOfRows = _pTable->getColumn(0).getNoOfRows();
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
	size_t currentNumberOfRows = table.getColumn(0).getNoOfRows();
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
	if (!exportFile.is_open()) {
		std::cout << "Failed to open file: " << _fileName << std::endl;
	}
	std::string stringToExport = getExportedString();
	exportFile << stringToExport; //_csvString;
	exportFile.close();
	if (exportFile.fail()) {
		std::cout << "Failed to write to file: " << _fileName << std::endl;
	}
}

void TableExport::ExportToCsvFile(const Table& table, std::string fileName = "exportTable.csv", const char delimiter = ',') const {
	std::ofstream exportFile;
	exportFile.open(fileName);
	exportFile << ExportToCsvString(table, delimiter);
	exportFile.close();
}

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
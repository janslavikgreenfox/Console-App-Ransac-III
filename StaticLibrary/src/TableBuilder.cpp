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

#include "TableBuilder.h"
#include "Table.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using Column = ConsoleAppRansacIINamespace::Core::Column;

namespace ConsoleAppRansacIINamespace {
namespace IO {

CsvTableBuilder::CsvTableBuilder(std::string csvFilename, int hdLines) 
	: _csvFilename{ csvFilename }, _hdLines{ hdLines }
{
	_currentTable = std::make_unique<Table>();
};


void CsvTableBuilder::buildTable() {
	// open the file
	std::ifstream inputFile;
	inputFile.open(_csvFilename, std::ios_base::in);

	// read the file line by line
	std::vector<std::string> allLines;
	std::string line;
	//std::istream& isHeader = std::getline(inputFile, line);
	while (std::getline(inputFile, line)) {
		if (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
			line.erase(line.size() - 1);
		}
		allLines.push_back(line);
	};

	// close the file
	inputFile.close();

	// tokenize the line
	constexpr char delimiter = ',';
	std::vector<std::vector<std::string>> tokenizedCsv{};
	for (const std::string& oneLine : allLines) {
		std::vector<std::string> tokenizedLine;
		std::stringstream ss(oneLine);
		std::string token;
		while (getline(ss, token, delimiter)) {
			tokenizedLine.push_back(token);
		}
		tokenizedCsv.push_back(tokenizedLine);
	}

	// Create a table
	_currentTable = std::make_unique<Table>((tokenizedCsv.at(0)).at(0));

	// create columns from the tokenized line
	for (size_t columnIndex = 0; columnIndex < tokenizedCsv.at(1).size(); ++columnIndex) {
		std::string columnHeader = tokenizedCsv.at(1).at(columnIndex);
		std::vector<double> columnValues;
		for (size_t rowIndex = 2; rowIndex < tokenizedCsv.size(); ++rowIndex) {
			if (columnIndex < tokenizedCsv.at(rowIndex).size()) {
				columnValues.push_back(stod(tokenizedCsv.at(rowIndex).at(columnIndex)));
			}
			else {
				columnValues.push_back(0.0);
			}
		}
		Column tmpColumn(columnValues, columnHeader);
		_currentTable->appendColumn(tmpColumn);
	}
}

std::unique_ptr<Table> CsvTableBuilder::getTable() {
	return std::move(_currentTable);
};

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
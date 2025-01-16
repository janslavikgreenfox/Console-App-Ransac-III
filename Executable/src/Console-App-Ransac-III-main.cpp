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

#include "Console-App-Ransac-III-main.h"
#include "TableFacade.h"
#include "TableBuilder.h"
#include "TableExport.h"
#include "Table.h"
#include "LinearModel.h"
#include "LeastSquaresFitStrategy.h"
#include "RANSACFitStrategy.h"
#include <iostream>
#include <string>

using CsvTableBuilder = ConsoleAppRansacIINamespace::IO::CsvTableBuilder;
using ITableBuilder = ConsoleAppRansacIINamespace::IO::ITableBuilder;
using TableFacade = ConsoleAppRansacIINamespace::IO::TableFacade;
using Table = ConsoleAppRansacIINamespace::Core::Table;
using Column = ConsoleAppRansacIINamespace::Core::Column;
using LeastSquaresFitStrategy = ConsoleAppRansacIINamespace::Fitting::LeastSquaresFitStrategy;
using RANSACFitStrategy = ConsoleAppRansacIINamespace::Fitting::RANSACFitStrategy;
using TableExport = ConsoleAppRansacIINamespace::IO::TableExport;
using ITableExport = ConsoleAppRansacIINamespace::IO::ITableExport;	
using TableExportToCsvFile = ConsoleAppRansacIINamespace::IO::TableExportToCsvFile;

int main(int argc, char* argv[])
{
	std::cout << "Ransac-III Console Application" << std::endl;

	std::string filename = std::string(argv[1]);

	if (filename.empty())
	{
		std::cout << "No filename provided. Exiting..." << std::endl;
		return -1;
	}

	// Build TableFacade
	std::unique_ptr<ITableBuilder> tableBuilder = std::make_unique<CsvTableBuilder>(filename, 1);
	constexpr char tableName[] = "Test Table";
	TableFacade tableFacade{ tableName, tableBuilder };

	//Column abcissa = pTable->getColumn(0);
	Column abcissa = tableFacade.getColumn(0);
	std::vector<double> abcissaValues = abcissa.getValuesForAllRows();
	//Column ordinate = pTable->getColumn(1);
	Column ordinate = tableFacade.getColumn(1);

	// Least Squares Fit
	cout << "Performing Least Squares Fit" << endl;
	LeastSquaresFitStrategy leastSquaresFitStrategy;
	LinearModel leastSquaresLinearFit;
	leastSquaresFitStrategy.fitModel(leastSquaresLinearFit, abcissa, ordinate);

	std::vector<double> leastSquaresOrdinateValues = leastSquaresLinearFit.getMultipleValuesAt(abcissaValues);
	Column leastSquaresOrdinate{ leastSquaresOrdinateValues, "Least Squares Fit"};
	tableFacade.appendColumn(leastSquaresOrdinate);

	// RANSAC Fit
	cout << "Performing RANSAC Fit" << endl;
	RANSACFitStrategy ransacFitStrategy;
	LinearModel ransacLinearFit;
	ransacFitStrategy.fitModel(ransacLinearFit, abcissa, ordinate);

	std::vector<double> ransacOrdinateValues = ransacLinearFit.getMultipleValuesAt(abcissaValues);
	Column ransacOrdinate{ ransacOrdinateValues, "RANSAC Fit" };
	//pTable->appendColumn(ransacOrdinate);
	tableFacade.appendColumn(ransacOrdinate);

	// Export Table
	cout << "Exporting Table to CSV file" << endl;
	//constexpr char outputFilename[] = "output.csv";
	//std::unique_ptr<ITableExport> tableExporter = std::make_unique<TableExportToCsvFile>(pTable, outputFilename, ',');
	//tableExporter->exportTable();
	tableFacade.exportTable();

	// Exit	
	return 0;
}

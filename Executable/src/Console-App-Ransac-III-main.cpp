// Console-App-Ransac-III.cpp : Defines the entry point for the application.
//

#include "Console-App-Ransac-III-main.h"
#include "TableBuilder.h"
#include "TableExport.h"
#include "Table.h"
#include "LinearModel.h"
#include "LeastSquaresFitStrategy.h"
#include "RANSACFitStrategy.h"
#include <iostream>
#include <string>

using CsvTableBuilder = ConsoleAppRansacIINamespace::IO::CsvTableBuilder;
using Table = ConsoleAppRansacIINamespace::Core::Table;
using Column = ConsoleAppRansacIINamespace::Core::Column;
using LeastSquaresFitStrategy = ConsoleAppRansacIINamespace::Fitting::LeastSquaresFitStrategy;
using RANSACFitStrategy = ConsoleAppRansacIINamespace::Fitting::RANSACFitStrategy;
using TableExport = ConsoleAppRansacIINamespace::IO::TableExport;

int main(int argc, char* argv[])
{
	std::cout << "Ransac-III Console Application" << std::endl;

	std::string filename = std::string(argv[1]);

	if (filename.empty())
	{
		std::cout << "No filename provided. Exiting..." << std::endl;
		return -1;
	}

	// Build Table
	cout << "Building Table from CSV file: " << filename << endl;
	CsvTableBuilder csvTableBuilder{ filename, 1 };
	csvTableBuilder.buildTable();
	std::unique_ptr<Table> pTable = csvTableBuilder.getTable();


	// Least Squares Fit
	cout << "Performing Least Squares Fit" << endl;
	Column abcissa = pTable->getColumn(0);
	std::vector<double> abcissaValues = abcissa.getValuesForAllRows();
	Column ordinate = pTable->getColumn(1);

	LeastSquaresFitStrategy leastSquaresFitStrategy;
	LinearModel leastSquaresLinearFit;
	leastSquaresFitStrategy.fitModel(leastSquaresLinearFit, abcissa, ordinate);

	std::vector<double> leastSquaresOrdinateValues = leastSquaresLinearFit.getMultipleValuesAt(abcissaValues);
	Column leastSquaresOrdinate{ leastSquaresOrdinateValues, "Least Squares Fit"};
	pTable->appendColumn(leastSquaresOrdinate);

	// RANSAC Fit
	cout << "Performing RANSAC Fit" << endl;
	RANSACFitStrategy ransacFitStrategy;
	LinearModel ransacLinearFit;
	ransacFitStrategy.fitModel(ransacLinearFit, abcissa, ordinate);

	std::vector<double> ransacOrdinateValues = ransacLinearFit.getMultipleValuesAt(abcissaValues);
	Column ransacOrdinate{ ransacOrdinateValues, "RANSAC Fit" };
	pTable->appendColumn(ransacOrdinate);

	// Export Table
	cout << "Exporting Table to CSV file" << endl;
	TableExport tableExport{};
	tableExport.ExportToCsvFile(*pTable, "output.csv",',');

	// Exit	
	return 0;
}

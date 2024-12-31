#pragma once

#include "Table.h"
#include "TableExport.h"
#include "TableBuilder.h"

namespace ConsoleAppRansacIINamespace {
namespace Core {

class TableFacade {
public:
	TableFacade(std::string& tableName) : _table{ tableName }, _tableExport{} {
	};

	TableFacade(const TableFacade& other) = default;

	TableFacade(TableFacade&& other) = default;

	TableFacade& operator=(const TableFacade& other) = default;

	TableFacade& operator=(TableFacade&& other) = default;

	~TableFacade() = default;

	//Table buildTable(const std::string& fileName, const char delimiter = ',') const {
	//	TableBuilder tableBuilder;
	//	return tableBuilder.buildTable(fileName, delimiter);
	//}

	size_t getNoOfColumns() const {
		return _table.getNoOfColumns();
	}

	size_t getCommonNoOfRows() const {
		return _table.getCommonNoOfRows();
	}

	void appendColumn(const Column& column) {
		_table.appendColumn(column);
	}

	Column getColumn(size_t columnIndex) const {
		return _table.getColumn(columnIndex);
	}

	double getCellValue(size_t cellRowIndex, size_t cellColumnIndex) const {
		return _table.getCellValue(cellRowIndex, cellColumnIndex);
	}

	void exportTableToCsvFile(const std::string& fileName, const char delimiter = ',') const {
		_tableExport.ExportToCsvFile(_table, fileName, delimiter);
	}

  private:
	  Table _table;
	  TableExport _tableExport;
	  //TableBuilder _tableBuilder;
};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
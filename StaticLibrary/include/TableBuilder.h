#pragma once

#include "Table.h"
#include <vector>
#include <string>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

class TableBuilder {
  public:
	virtual void buildTable() = 0;
	virtual std::unique_ptr<Table> getTable() = 0;
  protected:
	TableBuilder() {};
  private:
};


class CsvTableBuilder : public TableBuilder {
  private:
	std::string	_csvFilename;
	std::unique_ptr<Table>	_currentTable;
	//size_t		userSetNoHeaderRows;
  public:
	CsvTableBuilder(std::string csvFilename = "", int hdLines = 0);
	virtual void buildTable() override;
	std::unique_ptr<Table> getTable() override;
};

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
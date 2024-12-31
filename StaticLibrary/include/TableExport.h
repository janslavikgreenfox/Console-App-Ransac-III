#pragma once

#include "Table.h"
#include <string>

using Table = ConsoleAppRansacIINamespace::Core::Table;

namespace ConsoleAppRansacIINamespace {
namespace IO {

class TableExport {
  public:
    std::string ExportToCsvString(const Table& table, const char delimiter = ',') const;

    void ExportToCsvFile(const Table& table, const std::string fileName, const char delimiter) const;
};

} // namespace IO
} // namespace ConsoleAppRansacIINamespace
#include "ransac_bridge.h"
#include "TableBuilder.h"
#include "Table.h"
#include "RANSACFitStrategy.h"

std::unique_ptr<Table> table_from_csv(const std::string& path)
{
    auto builder = std::make_unique<ConsoleAppRansacIINamespace::IO::CsvTableBuilder>(path, 1);
    builder->buildTable();
    return builder->getTable();
}

double run_ransac(Table& table, double treshold)
{
    return 0.0;
} 
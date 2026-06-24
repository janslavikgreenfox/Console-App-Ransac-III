#pragma once
#include <memory>
#include <string>
#include "../../../StaticLibrary/include/Table.h"

using Table = ConsoleAppRansacIINamespace::Core::Table;

std::unique_ptr<Table> table_from_csv(const std::string& path);

double run_ransac(Table& table, double treshold); 
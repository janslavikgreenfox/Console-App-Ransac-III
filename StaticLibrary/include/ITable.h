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

#pragma once

#include "Column.h"
#include <iostream>
#include <string>

namespace ConsoleAppRansacIINamespace {
namespace Core {

	/**
	* @class Table
	* @brief The interface that represents a table of data.
	* A table is a collection of columns.
	* Each column is a collection of cells.
	* Each cell is a value.
	*
	* Features:
	* - Add a column to the table.
	* - Get the number of columns in the table.
	* - Get the name of the table.
	* - Get the common number of rows in all columns.
	* - Get a column from the table.
	* - Get a cell value from the table.
	* - Output the table to an output stream.
	* - Exception handling for out of bounds column indexes.
	* - Exception handling for bad memory allocation.
	*
	*/
	class ITable {
	public:

		/**
		* @brief Destructor
		*/
		virtual ~ITable() = default;

		/**
		* @brief Get name of the table.
		* @return The name of the table.
		*/
		virtual std::string getName() const = 0;

		/**
		* @brief Get the number of columns in the table.
		* @return The number of columns in the table.
		*/
		virtual size_t getNoOfColumns() const = 0;

		/**
		* @brief Get the common number of rows in all columns.
		* @return The common number of rows in all columns.
		*/
		virtual size_t getCommonNoOfRows() const = 0;

		/**
		* @brief Add a column to the table.
		* @param column The column to be added to the table.
		*/
		virtual void appendColumn(const Column& column) = 0;

		/**
		* @brief Get the column of the specified index from the table.
		* @param index The index of the column to get.
		* @return The column of the specified index.
		*/
		virtual Column getColumn(size_t index) const = 0;

		/**
		* @brief Get the value of the cell at the specified row and column indexes.
		* @param cellRowIndex The row index of the cell.
		* @param cellColumnIndex The column index of the cell.
		* @return The value of the cell at the specified row and column indexes.
		*/
		virtual double getCellValue(size_t cellRowIndex, size_t cellColumnIndex) const = 0;
	};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
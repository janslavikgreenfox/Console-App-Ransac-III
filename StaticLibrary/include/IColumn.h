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

#include "Common.h"

#include <vector>
#include <string>

namespace ConsoleAppRansacIINamespace {
namespace Core {

	/**
	* @class IColumn
	* @brief The interface class to represent a column of values.
	*
	* The 'IColumn' class provides a contract object to store a column of values.
	* Each column has a header (string) and a vector of values (doubles).
	*
	* Features:
	* - Add a row to the column.
	* - Get the number of rows in the column.
	* - Get the header of the column.
	* - Get all the values in the column.
	* - Get the value at a specified row index.
	* - Get the values at specified row indexes.
	* - Get the average of the values in the column.
	* - Output the column to an output stream.
	* - Exception handling for out of bounds row indexes.
	* - Exception handling for bad memory allocation.
	*
	*/
	class IColumn
	{
	public:
		
		virtual ~IColumn() = default;

		/**
		* @brief Add a row to the column values
		* @param value The double value to be added as a new row
		*/
		virtual void addRow(const double value) = 0;

		/**
		* @brief Get number of rows in the column
		* @return Number of the column rows
		*/
		virtual size_t getNoOfRows() const = 0;

		/**
		* @brief Get the column header
		* @return The header of the column
		*/
		virtual std::string getHeader() const = 0;

		/**
		* @brief Get all rows from the Column
		* @return A vector of all the values in the column
		*/
		virtual std::vector<double> getAllRows() const = 0;

		/**
		* @brief Get the value at a specified row index
		* @param specifiedRowIndex The index of the row to get the value from
		* @return The value at the specified row index
		*/
		virtual double getOneRow(const size_t& specifiedRowIndex) const = 0;

		/**
		* @brief Get the values at specified row indexes
		* @param specifiedRowIndexes A vector of picked indexes of the rows to get the values from
		* @return A vector of the values at the specified row indexed
		*/
		//virtual IColumn getSpecifiedRows(const std::vector<size_t>& specifiedRowIndexes) const = 0;

		/**
		* @brief Get the average of the values in the column
		* @return The average of the values in the column
		*/
		virtual double getAverage() const = 0;
	};

} // namespace Core
} // namespace ConsoleAppRansacIINamespace

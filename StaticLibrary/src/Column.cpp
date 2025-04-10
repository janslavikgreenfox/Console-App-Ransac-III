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

#include <vector>
#include <string>
#include <iostream>
#include <set>
#include "Column.h"

namespace ConsoleAppRansacIINamespace {
namespace Core {

Column::Column(const std::vector<double>& rowVector, const std::string header)
	: _colHeader(header), _noRows(rowVector.size())
	 {
	    try {
	      _colValues.reserve(rowVector.size());
	    }
		catch (const std::bad_alloc& e)
		{ 
			std::string exceptionMessage{ "Not enough memory to allocate Column |" };
			exceptionMessage.append(getIndexAndColumnNameMessage(_noRows));
			throw BadAlloc(exceptionMessage);
		}
		_colValues = rowVector;
};

void Column::addRow(const double value) {
	try {
		_colValues.emplace_back(value);
		_noRows++;
	}
	catch (const std::bad_alloc& e) {
		std::string exceptionMessage{ "Not enough memory to allocate an additional row to a column |" };
		exceptionMessage.append(getIndexAndColumnNameMessage(_noRows));
		throw BadAlloc(exceptionMessage);
	}
}

std::string Column::getIndexAndColumnNameMessage(const size_t& index) const {
	std::string message{};
	message.append("Index: ").append(std::to_string(index));
	message.append(" Column name: ").append(getHeader());
	return message;
}


std::vector<double> Column::getValuesAtSelectedIndexes(const std::vector<size_t>& selectedIndexes) const {
	std::vector<double> result{};
	for (size_t index = 0; index < selectedIndexes.size(); index++) {
		if (index + 1 > _noRows) {
			std::string exceptionMessage{ "The index is out of bounds |" };
			exceptionMessage.append(getIndexAndColumnNameMessage(index));
			throw RowIndexOutOfBounds(exceptionMessage);
		}
		else
		{
			result.push_back(_colValues.at(selectedIndexes.at(index)));
		}
	}
	return result;
}

size_t Column::getNoOfRows() const { 
	return _noRows; 
}

std::string Column::getHeader() const { 
	return _colHeader; 
}

std::vector<double> Column::getAllRows() const { 
	return _colValues;	
}


double Column::getOneRow(const size_t& specifiedRowIndex) const {
	std::vector<size_t> selectedIndexes{ specifiedRowIndex };
	return getValuesAtSelectedIndexes(selectedIndexes)[0];
};


Column Column::getSpecifiedRows(const std::vector<size_t>& specifiedRowIndexes) const {
	std::vector<double> resultValues{ getValuesAtSelectedIndexes(specifiedRowIndexes) };
	std::string selectedPostfix{"- selected"};
	std::string resultHeader = getHeader().append(selectedPostfix);

	return Column{ resultValues, resultHeader };
}

std::ostream& operator<<(std::ostream& os, const Column& column) {
	for (double item : column._colValues) {
		os << (item) << std::endl;
	};
	return os;
}

double Column::getAverage() const {
	double mean = 0;
	size_t counter = 0;
	for (auto item : _colValues) {
		++counter;
		mean += (item - mean) / counter;
	}
	return mean;
}

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
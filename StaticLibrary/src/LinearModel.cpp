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

#include <limits>
#include <set>
#include "LinearModel.h"


namespace ConsoleAppRansacIINamespace {
namespace Core {

LinearModel& LinearModel::operator=(const LinearModel& other) {
	if (this != &other) {
		_yInterceptAlpha = other._yInterceptAlpha;
		_slopeBeta = other._slopeBeta;
	}
	return *this;
}

LinearModel& LinearModel::operator=(LinearModel&& other) noexcept {
	if (this != &other) {
		_yInterceptAlpha = other._yInterceptAlpha;
		_slopeBeta = other._slopeBeta;
	}
	return *this;
}

bool LinearModel::isEqualTo(const LinearModel& other) const {
	return (_yInterceptAlpha == other.getValueAt0()) && (_slopeBeta == other.getSlope());
}

double LinearModel::getValueAt(const double& abcissa) {
	return _yInterceptAlpha + _slopeBeta * abcissa;
}

vector<double> LinearModel::getMultipleValuesAt(const vector<double>& abcisses) {
	// Dependency inversion principle broken?
	vector<double> result;
	for (size_t index = 0; index < abcisses.size(); index++) {
		result.push_back(getValueAt(abcisses.at(index)));
	}
	return result;
}

double LinearModel::sumOfSquaredResiduals(const Column& abcissa, const Column& ordinate) {
	double cummulativeSquare = 0;
	for (size_t sharedIndex = 0; sharedIndex < abcissa.getNoRows(); sharedIndex++) {
		vector<double> modelValueX;
		modelValueX.push_back(abcissa.getValueForOneSpecifiedRow(sharedIndex));
		vector<double> modelValueY = this->getMultipleValuesAt(modelValueX);
		double Y = ordinate.getValueForOneSpecifiedRow(sharedIndex);
		cummulativeSquare += (modelValueY.at(0) - Y) * (modelValueY.at(0) - Y);
	}
	return cummulativeSquare;
}

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
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

#include<limits>
#include <memory>
#include <cmath>

namespace ConsoleAppRansacIINamespace {
namespace Core {


/**
* @brief A small value used to compare floating point numbers.
*
* @see https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
*/
constexpr double epsilon{ std::numeric_limits<double>::epsilon() };


/**
* @brief Compare two double values for equality.
* @param a The first double value.
* @param b The second double value.
* @return True if the two values are equal, false otherwise.
*/
bool doublesAreEqual(double a, double b);

} // namespace Core
} // namespace ConsoleAppRansacIINamespace
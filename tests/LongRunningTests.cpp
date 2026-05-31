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

#include "Common.h"
#include "Column.h"
#include <gtest/gtest.h>
#include <iostream>

using Column = ConsoleAppRansacIINamespace::Core::Column;

// namespace UnitTest
// {
// TEST(LongRunningTest, ExtremeLongColumn) {
//     // Arrange
//     constexpr size_t hugeVectorSize = 2000000000;
//     std::vector<double> hugeVector(hugeVectorSize, 1.414);

//     // Act & Assert
//     EXPECT_THROW({
//         Column column{hugeVector, "Really huge vector"};
//     }, Column::BadAlloc);
// }
// }

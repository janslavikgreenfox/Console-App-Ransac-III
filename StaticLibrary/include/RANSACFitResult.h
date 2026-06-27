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

#include "TableFacade.h"
#include "LinearModel.h"

#include <vector>


namespace ConsoleAppRansacIINamespace {
namespace RustInterface {

    using TableFacade = ConsoleAppRansacIINamespace::IO::TableFacade;
    using LinearModel = ConsoleAppRansacIINamespace::Core::LinearModel;

/***
 * @class RansacFitResult
 * 
 */
class RansacFitResultPOD {
public:
    RansacFitResultPOD(TableFacade&& tableFacade, LinearModel linearModel)
    :  
    tableFacade_(std::move(tableFacade)),
    linearModel_(linearModel)
    { }

    std::vector<double> getInputDataAbcissa(){
        return tableFacade_.getColumn(0).getAllRows();
    }

    std::vector<double> getInputDataOrdinate(){
        return tableFacade_.getColumn(1).getAllRows();
    }

    LinearModel getLinearModel(){
        return linearModel_;
    }
    
private:
    TableFacade tableFacade_;

    LinearModel linearModel_;
}

} // namespace RustInterface
} // namespace ConsoleAppRansacIINamespace
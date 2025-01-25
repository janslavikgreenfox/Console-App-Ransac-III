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

#include <string>
#include <iostream>
#include <fstream>

namespace ConsoleAppRansacIINamespace {
namespace CLI {

class CommandLineParser{
public:
	/**
	* @brief Constructor
	* @param argc Number of arguments
	* @param argv Array of arguments
	*/
	CommandLineParser(int argc, char* argv[]);

	/**
	* @brief Destructor
	*/
	~CommandLineParser();

	/**
	* @brief Get the filename
	* @return Filename
	*/
	std::string getFilename() const;

private:
	/**
	* @brief Print the usage to the console
	*/
	void printUsage() const;
	/**
	* @brief Print the help to the console
	*/
	void printHelp() const;
	/**
	* @brief Check if the file exists
	* @param filename Filename of the file to check
	* @note Exits the program if the file does not exist
	*/
	void exitIfFileNotFound(const std::string& filename) const;
	/**
	* @brief Check if the file is a CSV file
	* @param filename Filename of the file to check
	*/
	void exitIFileIsNotCsv(const std::string& filename) const;

	
	/**
	* @brief Filename
	*/
	std::string _filename;
};

} // namespace CLI
} // namespace ConsoleAppRansacIINamespace

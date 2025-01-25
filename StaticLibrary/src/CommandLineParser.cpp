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

#include "CommandLineParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

namespace ConsoleAppRansacIINamespace {
namespace CLI {

CommandLineParser::CommandLineParser(int argc, char* argv[]) {
	if (argc != 2) {
		printUsage();
		exit(EXIT_FAILURE);
	}
	std::string argument = std::string(argv[1]);
	if (argument == "-h" || argument == "--help") {
		printHelp();
		exit(EXIT_SUCCESS);
	}

	exitIfFileNotFound(argument);
	exitIFileIsNotCsv(argument);
	_filename = argument;
}

void CommandLineParser::exitIfFileNotFound(const std::string& filename) const {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cout << "File not found. Exiting..." << std::endl;
		exit(EXIT_FAILURE);
	}
	file.close();
}

void CommandLineParser::exitIFileIsNotCsv(const std::string& filename) const {
	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (extension != "csv") {
		std::cout << "File is not a CSV file. Exiting..." << std::endl;
		exit(EXIT_FAILURE);
	}
}

std::string CommandLineParser::getFilename() const {
	return _filename;
}

void CommandLineParser::printUsage() const {
	std::cout << "Usage: Console-App-Ransac-III <filename>" << std::endl;
	std::cout << "Use -h or --help for more information." << std::endl;
}

void CommandLineParser::printHelp() const {
	std::cout << "Help: Console-App-Ransac-III <filename>" << std::endl;
	std::cout << "This program reads a CSV file and fits a line to the data using the RANSAC algorithm." << std::endl;
	std::cout << "The CSV file should have two columns: x and y." << std::endl;
	std::cout << "The program outputs the inliers and outliers to the console." << std::endl;
	std::cout << "The program also outputs the parameters of the fitted line to the console." << std::endl;
	printUsage();
}

CommandLineParser::~CommandLineParser() {
}

} // namespace CLI
} // namespace ConsoleAppRansacIINamespace

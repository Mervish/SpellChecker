// Spell Checker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "DataHandler.h"

const std::string usageInfo("usage: [input path] [output path] ");
constexpr int expectedArgs = 3;

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    //Arguments checking
    if (argc < expectedArgs) {
        std::cerr << usageInfo << std::endl;
        return 1;
    }
    if (argc > expectedArgs) {
        std::cerr << "Too many arguments" << std::endl << usageInfo << std::endl;
        return 1;
    }
    //Arguments handling
    fs::path inputPath(argv[1]);
    fs::path outputPath(argv[2]);

    if(!fs::exists(inputPath)) {
        std::cerr << "Error: input path is not valid or don't exists." << std::endl; //Nothing i can do without input file
        return 1;
    }

    //Check if output exists
    if (fs::exists(outputPath)) {
        std::string command;
        std::cout << "Output file exists. Rewrite? y/n" << std::endl;
        std::cin >> command;
        if (command != "y") {
            std::cout << "Execution stopped by user." << std::endl;
            return 1;
        }
    }

    //Reading files
    std::ifstream inputStream(inputPath);

    if (inputStream.is_open())
    {
        std::stringstream strbuffer;
        strbuffer << inputStream.rdbuf();
        
        DataHandler handler(strbuffer.str()); //Start parsing        
    
        if (handler.isInitialised()) {
            std::ofstream outputStream(outputPath);
            outputStream << handler.checkSpelling();
        }
        else {
            std::cerr << "Error: failed to parse input file. " << handler.getErrorString() << std::endl;
        }
    }

    std::cout << "This is fine!\n";
    return 0;
}
#include "ProcessCommandLine.hpp"
#include "TransformChar.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    // Process command line arguments
    const bool cmdLineStatus{processCommandLine(
        cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)};

    // Any failure in the argument processing means we can't continue
    // Use a non-zero return value to indicate failure
    if (!cmdLineStatus) {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    if (!inputFile.empty()) {
        // loop over each character from input file
        std::ifstream inFile{inputFile};
        bool ok_to_read = inFile.good();
        if (not ok_to_read) {
            std::cerr << "Error: could not read from input file " << inputFile
                      << std::endl;
            return 1;
        }
        while (inFile >> inputChar) {
            inputText += transformChar(inputChar);
        }
    } else {
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    // Print out the transliterated text
    if (!outputFile.empty()) {
        std::ofstream outFile{outputFile};
        bool ok_to_write = outFile.good();
        if (not ok_to_write) {
            std::cerr << "Error: could not write to output file " << outputFile
                      << std::endl;
            return 1;
        }
        outFile << inputText << std::endl;
    } else {
        std::cout << inputText << std::endl;
    }

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}

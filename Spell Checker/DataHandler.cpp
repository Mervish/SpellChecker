
#include <vector>
#include <algorithm>

#include "DataHandler.h"
//#include "StringLibrary.h"

DataHandler::DataHandler(std::string&& input)
{
    std::string inputString = std::move(input);
    std::replace(inputString.begin(), inputString.end(), '\n', ' '); // replace newline with spaces
    //remove duplicate spaces
    inputString.erase(std::unique(inputString.begin(), inputString.end(), 
        [](auto& lhs, auto& rhs) { return (lhs == rhs) && (lhs == ' '); }), inputString.end());
    
    auto list = StringLibrary::splitString(inputString, delim);

    //Having text after second '===' is not an error. We will just ignore it
    if (list.size() >= 2) {
        if (list[0].empty()) {
            errorString = "No words in dictionary.";
            return;
        }            
        if (list[1].empty()) {
            errorString = "No words to process.";
            return;
        }

        dictionary.setWords(StringLibrary::splitString(StringLibrary::cleanString(list[0]), " "));
        words = StringLibrary::splitString(StringLibrary::cleanString(list[1]), " ");
    }
    else {
        errorString = "Wrong formatting of input file.";
        return;
    }
    initialized = true;
}

std::string DataHandler::checkSpelling()
{
    std::string output;

    for (auto& word : words) {
        dictionary.correct(word);
        output += word + ' ';
    }
    output.pop_back();
    return output;
}


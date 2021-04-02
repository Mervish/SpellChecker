#pragma once
#ifndef SPELL_CHECK_DATA_HANDLER
#define SPELL_CHECK_DATA_HANDLER

//#include <string>
//#include <vector>

#include "SpellChecker.h"

class DataHandler final
{
private:
	const std::string delim = "===";
	
	bool initialized = false;
	std::string errorString;

	std::vector<std::string> words;
	SpellChecker dictionary;

public:
	DataHandler(std::string &&input);
	std::string checkSpelling();

	//getters
	bool isInitialised() { return initialized; };
	std::string getErrorString() { return errorString; };

};

#endif

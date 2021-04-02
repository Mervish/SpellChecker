#pragma once
#ifndef SPELL_CHECK_SPELL_CHECKER
#define SPELL_CHECK_SPELL_CHECKER

//#include <vector>
//#include <string>
#include <algorithm>
#include <iterator>

#include "StringLibrary.h"

struct dictionaryEntry
{
	std::string value;
	std::string valueLow;
	dictionaryEntry(const std::string& input) : value(input) {
		std::transform(value.begin(), value.end(), std::back_inserter(valueLow), [](auto c) { return tolower(c); });
	}

	bool operator < (const dictionaryEntry& other) noexcept
	{
		return this->valueLow < other.valueLow;
	}

	bool operator == (const dictionaryEntry& other) noexcept
	{
		return this->valueLow == other.valueLow;
	}
};

struct candidate
{
	size_t index;
	unsigned int weight;
	candidate(unsigned int _index, unsigned int _weight) : index(_index), weight(_weight) {}
};

class SpellChecker final
{

private:
	std::vector<dictionaryEntry> dictionary;
	void optimise();
		
public:
	void setWords(const std::vector<std::string>& input);
	
	std::string& correct(std::string &input);
};

#endif //SPELL_CHECK_SPELL_CHECKER
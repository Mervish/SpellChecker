#include "SpellChecker.h"
//#include "StringLibrary.h"

void SpellChecker::setWords(const std::vector<std::string>& input)
{
	for (auto& word : input){
		dictionary.emplace_back(word);
	}
	optimise();
}

void SpellChecker::optimise() //remove duplicates (and sort)
{
	std::sort(dictionary.begin(), dictionary.end());
	dictionary.erase(std::unique(dictionary.begin(), dictionary.end()), dictionary.end());
	dictionary.shrink_to_fit();
}

std::string& SpellChecker::correct(std::string& input)
{
	std::string inputLow;
	transform(input.begin(), input.end(), back_inserter(inputLow), [](auto c) { return tolower(c); });
	//Let's find if we have 
	auto lower = lower_bound(dictionary.begin(), dictionary.end(), inputLow, [](const  dictionaryEntry& entry, const std::string& value) {return entry.valueLow < value; });
	if (lower != dictionary.end())
	{
		if ((*lower).valueLow == inputLow) {
			return input;
		}
	}
	
	//Gather candidates for replacement
	std::vector<candidate> candidates;
	for (size_t i = 0; i < dictionary.size(); ++i) {
		if (auto weight = StringLibrary::match(dictionary.at(i).valueLow, inputLow)) {
			candidates.emplace_back(i, weight.value());
		}
	}
	
	//Only keep candidates with lower level of necessary changes
	if (any_of(candidates.begin(), candidates.end(), [](candidate can) { return 1 == can.weight; })) {
		candidates.erase(remove_if(candidates.begin(), candidates.end(), [](candidate can) { return can.weight != 1; }), candidates.end());
	}
	//Check what we got
	switch (candidates.size())
	{
	case 0: //No matches
		input = '{' + input + "?}";
		break;
	case 1: //One match - replace
		input = dictionary.at(candidates.front().index).value;
		break;
	default: //Many matches - list
		input = '{';
		for (auto& candidate : candidates) {
			input += dictionary.at(candidate.index).value + ' ';
		}
		input.back() = '}';
		break;
	}

	return input;
}

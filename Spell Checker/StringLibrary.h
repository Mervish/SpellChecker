#pragma once
#ifndef SPELL_CHECK_STRING_LIBRARY
#define SPELL_CHECK_STRING_LIBRARY

#include <string>
#include <vector>
#include <optional>

class StringLibrary
{

public:
	//This should be a part of stl
	static std::vector<std::string> splitString(const std::string& input, const std::string& delim)
	{
		std::vector<std::string> stringList;
		size_t begin = 0;
		size_t end = 0;

		do //We must do it at least once 
		{
			end = input.find(delim, begin);
			stringList.emplace_back(input.substr(begin, end - begin));
			begin = end + delim.size();
		} while (end != std::string::npos);

		return stringList;
	};

	static std::string& cleanString(std::string& input)
	{
		while (input.front() == ' ')
		{
			input.erase(input.begin());
			//input.erase(0, 1);
		}
		while (input.back() == ' ') {
			input.pop_back();
		}
		return input;
	};

	static std::optional<size_t> match(const std::string& one, const std::string& other)
	{
		size_t sizeDifference = std::max(one.size(), other.size()) - std::min(one.size(), other.size());

		//Words can't be different by more then two letters
		if (sizeDifference <= 2) {
			if (sizeDifference > 0) {
				bool res;
				if (one.size() > other.size()) {
					res = match_different(other, one);
				}
				else {
					res = match_different(one, other);
				}
				if (res)
					return sizeDifference;
			}
			else
				if (match_same(one, other))
					return size_t(2);
		}
		return {};
	};

private:
	static bool match_same(const std::string& one, const std::string& other)
	{
		size_t mod = 0; //modifier
		bool modified = false; //that we had modification
		int matchCount = 0;
		for (size_t ind = 0; ind < one.size(); )
		{
			if (ind + mod < other.size()) {
				if (one.at(ind) != other.at(ind + mod)) {
					if (modified) {
						return false;
					}
					if (mod > 0) {
						modified = true;
						mod = 0;
						++ind;
					}
					else {
						++mod;
					}
				}
				else {
					++matchCount;
					++ind;
				}
			}
			else
				break;
		}

		if (one.size() - matchCount > 1)
			return false;

		return true;
	};

	static bool match_different(const std::string& smaller, const std::string& bigger)
	{
		size_t mod = 0; //our offset for bigger string
		bool adjanced = false;
		size_t ind = 0;
		while (ind < smaller.size())
		{
			//This actually prevents mod from getting bigger then dif
			if (ind + mod < bigger.size()) {
				//Is letters don't match, we increase offset and check the same pair
				if (smaller.at(ind) != bigger.at(ind + mod)) {
					//If adjanced then fail
					if (adjanced)
						return false;
					else
						adjanced = true;
					++mod;
				}
				else {
					if (adjanced)
						adjanced = false;
					++ind;
				}
			}
			else {
				return false;
			}
		}
		auto dif = bigger.size() - smaller.size();
		//If adjanced, then we can't add more letters. Otherwise we can add only one.
		if (dif - mod > static_cast<size_t>(!adjanced)) //
			return false;

		return true;
	};
};

#endif //SPELL_CHECK_STRING_LIBRARY
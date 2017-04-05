#ifndef COCCOCTESTTASK_PARSER_H
#define COCCOCTESTTASK_PARSER_H

#include <map>
#include <string>

class Parser{
public:
	static bool validateInputNumber(std::string inputNumber);
	static std::string getDecimalPlace(int lengthOfString, int index);
	std::string generateTextRepresentation(std::string inputNumber);

	// to change language, just change these member variables or via setter
	const std::string EN_LANGUAGE = "en";
	std::string language = EN_LANGUAGE;
	std::map <const std::string, std::string> decimalPlacePostfixLanguageMapping;
	std::map <const char, std::string> numberLanguageMapping;

	// per-language implementation, this one is used by English
	std::map <const std::string, std::string> eleventhsLanguageMapping;
	std::map <const char, std::string> tenthsLanguageMapping;
	
	Parser() :
	decimalPlacePostfixLanguageMapping({
		{ "tenths", "ty" },
		{ "hundreds", " hundred" },
		{ "thousands", " thousand" },
		{ "millions", " million" },
		{ "billions", " billion" }
	}), numberLanguageMapping({
		{ '0', "" },
		{ '1', "one" },
		{ '2', "two" },
		{ '3', "three" },
		{ '4', "four" },
		{ '5', "five" },
		{ '6', "six" },
		{ '7', "seven" },
		{ '8', "eight" },
		{ '9', "nine" }
	}), // specific for English
		eleventhsLanguageMapping({
		{ "10", "ten" },
		{ "11", "eleven" },
		{ "12", "twelve" },
		{ "13", "thirteen" },
		{ "14", "fourteen" },
		{ "15", "fifteen" },
		{ "16", "sixteen" },
		{ "17", "seventeen" },
		{ "18", "eightteen" },
		{ "19", "nineteen" }
	}), tenthsLanguageMapping({
		{ '0', "" },
		{ '2', "twen" },
		{ '3', "thir" },
		{ '4', "for" },
		{ '5', "fif" },
		{ '6', "six" },
		{ '7', "seven" },
		{ '8', "eight" },
		{ '9', "nine" }
	}) {};
protected:
	std::string getDecimalPlacePostfix(int index, std::string wholeNumber);
	std::string getLiteral(char number, std::string decimalPlace);

	// specific to English
	std::string getEleventhLiteral(std::string number);
};

#endif 
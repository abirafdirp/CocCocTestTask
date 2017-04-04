#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Parser.h"

// the maximum decimal places of this program is until hundreds of billions, although it can be easily extended

// In English, tenths text representation does not follows the literal translation e.g. 21 is not "two" +  tenths's postfix + "one",
// rather than "twen" (which is not literal ones translation) + the english tenth's postfix, which is "ty" + "one".

// Compared to Indonesian, which use exact translation,
// the text representation will be "dua" (the exact literal translation of 2) + tenth's postfix + "satu" (the exact translation of 1).

// Besides that, 10-19 in English have their own words (Indonesian too).
// So to support more languages, we need to define per-language implementation at corresponding functions.

bool Parser::validateInputNumber(std::string inputNumber){
	if (inputNumber.find_first_not_of("0123456789") != std::string::npos || (inputNumber.length() != 1 && inputNumber[0] == '0' || inputNumber.length() > 12)) {
		return false;
	}
	return true;
}

std::string Parser::getPostfix(int lengthOfString, int index, char number){
	std::string postfix;
	int indexFromRight = lengthOfString - index;

	if (number == '0' && indexFromRight % 3 != 1) {
		postfix = "";
	}
	// exception number eight in English, only add 'y'
	else if (number == '8' && postfix == "ty" && this->language == this->EN_LANGUAGE) {
		postfix = "y";
	}
	else if (indexFromRight % 3 == 2) {
		postfix = decimalPlacePostfixLanguageMapping.at("tenths");
	}
	else if (indexFromRight % 3 == 0) {
		postfix = decimalPlacePostfixLanguageMapping.at("hundreds");
	}
	else if (indexFromRight == 4){
		postfix = decimalPlacePostfixLanguageMapping.at("thousands");
	}
	else if (indexFromRight == 7) {
		postfix = decimalPlacePostfixLanguageMapping.at("millions");
	}
	else if (indexFromRight == 10) {
		postfix = decimalPlacePostfixLanguageMapping.at("billions");
	}
	// ones
	else {
		postfix = "";
	}
	return postfix;
}

std::string Parser::getDecimalPlace(int lengthOfString, int index){
	// decimal places will be reset at modulo 3, I don't know what to call it and it's definitely not called decimal place
	std::string decimalPlace;
	int indexFromRight = lengthOfString - index;
	if (indexFromRight % 3 == 1) {
		decimalPlace = "ones";
	}
	else if (indexFromRight % 3 == 2){
		decimalPlace = "tenths";
	}
	else if (indexFromRight % 3 == 0) {
		decimalPlace = "hundreds";
	}
	return decimalPlace;
}

// specific to english
std::string Parser::getEleventhLiteral(std::string number){
	return this->eleventhsLanguageMapping.at(number);
}

std::string Parser::getLiteral(char number, std::string decimalPlace){
	if (decimalPlace == "ones" || decimalPlace == "hundreds" ){
		return this->numberLanguageMapping.at(number);
	}
	// specific to english
	else if (this->language == this->EN_LANGUAGE) {
		return this->tenthsLanguageMapping.at(number);
	}
}

// used to remove multiple whiteps
bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }


std::string Parser::generateTextRepresentation(std::string inputNumber){
	bool validated = Parser::validateInputNumber(inputNumber);
	if (!validated) {
		throw std::invalid_argument("Your input is incorrect, you have illegal character/s or the input is too long\n");
	}

	char currentNumber, nextNumber;
	bool hasNextNumber = false;
	std::string postfix = "", numberLiteral, decimalPlace, output;
	int inputNumberLength = inputNumber.length();

	// special case for only zero
	if (inputNumberLength == 1 && inputNumber[0] == '0') {
		return "zero";
	}

	for (int i = 0; i < inputNumberLength; i++){
		currentNumber = inputNumber[i];

		if (i != inputNumberLength - 1) {
			hasNextNumber = true;
			nextNumber = inputNumber[i + 1];
		}
		else {
			hasNextNumber = false;
		}

		decimalPlace = Parser::getDecimalPlace(inputNumberLength, i);

		// specific to English for 10-19
		if (currentNumber == '1' && hasNextNumber && decimalPlace == "tenths" && this->language == this->EN_LANGUAGE) {
			std::string eleventhNumber(1, currentNumber);
			eleventhNumber = eleventhNumber + nextNumber;
			numberLiteral = this->getEleventhLiteral(eleventhNumber);

			i++;
			postfix = this->getPostfix(inputNumberLength, i, currentNumber);
		}
		else {
			numberLiteral = Parser::getLiteral(currentNumber, decimalPlace);
			postfix = this->getPostfix(inputNumberLength, i, currentNumber);
		}
		output = output + numberLiteral + postfix + " ";
		
	};

	std::string::iterator new_end = std::unique(output.begin(), output.end(), BothAreSpaces);
	output.erase(new_end, output.end());

	return output;
}


#include <iostream>
#include <stdio.h>

#include "Parser.h"

int main(){
	std::string textRepresentation;
	char retry;
	Parser *parser = new Parser();

	while (1) {
		std::cout << "Enter your number to be converted to its text representation (maximum is hundreds of billions): ";

		std::string inputNumber;

		// use getline to allow whitespace in the beginning in order to trigger bad input
		std::cin.clear();
		fflush(stdin);
		std::getline(std::cin, inputNumber);

		try {
			textRepresentation = parser->generateTextRepresentation(inputNumber);
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what();
			return 0;
		}

		std::cout << "The text representation is: " << textRepresentation << "\n";
		std::cout << "Do you want another input? [y/n]: ";
		std::cin >> retry;
		if (retry == 'n') {
			break;
		}
		else if (retry != 'y') {
			std::cout << "invalid character, exiting program \n";
			break;
		}

	}
	return 0;
}
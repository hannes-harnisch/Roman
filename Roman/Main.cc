#include <cstdio>
#include <regex>
#include <string>
#include <vector>

import Conversion;

const std::regex NumberRegex("\\d+");
const std::regex NumeralRegex("[IVXLCDM]+");

void processNumberToNumeral(const std::string& input)
{
	int number {std::stoi(input)};
	std::string numeral {numberToNumeral(number)};

	if(numeral.empty())
		std::printf("Cannot convert %i to a Roman numeral.", number);
	else
		std::printf("%s", numeral.data());
}

void processNumeralToNumber(const std::string& input)
{
	int number {numeralToNumber(input)};
	if(number)
		std::printf("%i", number);
	else
		std::printf("%s is not a valid Roman numeral.", input.data());
}

int main(int argc, char* argv[])
{
	std::vector<std::string> commandLineArgs(argv + 1, argv + argc);
	for(auto& input : commandLineArgs)
	{
		input = toUpper(input);

		std::smatch match;
		if(std::regex_match(input, match, NumberRegex))
			processNumberToNumeral(input);
		else if(std::regex_match(input, match, NumeralRegex))
			processNumeralToNumber(input);
		else
			std::printf("Invalid input.");

		std::printf("\n");
	}
}

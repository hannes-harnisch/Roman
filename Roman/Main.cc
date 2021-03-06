#include <cstdio>
#include <regex>
#include <string>
#include <vector>

import Conversion;

void processNumberToNumeral(std::string const& input)
{
	int number	 = std::stoi(input);
	auto numeral = numberToNumeral(number);

	if(numeral)
		std::printf("%s\t->\t%s", input.data(), numeral->data());
	else
		std::printf("Cannot convert %i to a Roman numeral.", number);
}

void processNumeralToNumber(std::string const& input)
{
	auto number = numeralToNumber(input);
	if(number)
		std::printf("%s\t->\t%i", input.data(), *number);
	else
		std::printf("%s is not a valid Roman numeral.", input.data());
}

int main(int argc, char* argv[])
{
	std::regex const numberRegex("[-\\d]+");
	std::regex const numeralRegex("[IVXLCDM]+");
	std::vector<std::string> commandLineArgs(argv + 1, argv + argc);

	for(auto& input : commandLineArgs)
	{
		input = toUpper(input);

		std::smatch match;
		if(std::regex_match(input, match, numberRegex))
			processNumberToNumeral(input);
		else if(std::regex_match(input, match, numeralRegex))
			processNumeralToNumber(input);
		else
			std::printf("Invalid input.");

		std::printf("\n");
	}
}

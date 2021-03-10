module;
#include <cctype>
#include <sstream>
export module Conversion;

struct RomanNumeralMapping
{
	int Number;
	std::string Numeral;
};

const RomanNumeralMapping Map[] {
	{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
	{40, "XL"},	 {10, "X"},	  {9, "IX"},  {5, "V"},	   {4, "IV"},  {1, "I"},
};

export std::string numberToNumeral(int number)
{
	if(number < 1)
		return {};

	std::stringstream numeral;
	for(auto& mapping : Map)
	{
		while(number - mapping.Number >= 0)
		{
			number -= mapping.Number;
			numeral << mapping.Numeral;
		}
	}
	return numeral.str();
}

export int numeralToNumber(const std::string& numeral)
{
	int number {}, mappingsToSkip {};
	auto numeralPos {numeral.begin()};
	for(auto& mapping : Map)
	{
		if(mappingsToSkip)
		{
			--mappingsToSkip;
			continue;
		}
		if(numeralPos < numeral.end() - 1 && std::string({*numeralPos, numeralPos[1]}) == mapping.Numeral)
		{
			numeralPos += 2;
			number += mapping.Number;
			mappingsToSkip = mapping.Number % 9 == 0 ? 3 : 1;
		}
		while(numeralPos < numeral.end() && std::string({*numeralPos}) == mapping.Numeral)
		{
			++numeralPos;
			number += mapping.Number;
		}
	}
	if(numeralPos < numeral.end())
		return 0;
	return number;
}

export std::string toUpper(const std::string& str)
{
	std::string upper(str.length(), '\0');
	auto upperPos {upper.begin()};
	for(char character : str)
		*upperPos++ = std::toupper(character);
	return upper;
}

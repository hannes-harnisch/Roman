module;
#include <cctype>
#include <optional>
#include <sstream>
#include <string_view>
export module Conversion;

struct RomanNumeralMapping
{
	int number;
	std::string_view numeral;
};

constexpr RomanNumeralMapping Map[] {
	{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"},
	{40, "XL"},	 {10, "X"},	  {9, "IX"},  {5, "V"},	   {4, "IV"},  {1, "I"},
};

export std::optional<std::string> numberToNumeral(int number)
{
	if(number < 1)
		return {};

	std::stringstream numeral;
	for(auto& mapping : Map)
	{
		while(number - mapping.number >= 0)
		{
			number -= mapping.number;
			numeral << mapping.numeral;
		}
	}
	return numeral.str();
}

int firstDecimalDigit(int n)
{
	while(n >= 10)
		n /= 10;
	return n;
}

export std::optional<int> numeralToNumber(const std::string& numeral)
{
	int number {}, mappingsToSkip {};
	auto chars = numeral.begin();
	for(auto& mapping : Map)
	{
		if(mappingsToSkip)
		{
			--mappingsToSkip;
			continue;
		}

		bool moreThanOneCharLeft = chars < numeral.end() - 1;
		if(moreThanOneCharLeft && std::string_view(chars, chars + 2) == mapping.numeral)
		{
			chars += 2;
			number += mapping.number;
			mappingsToSkip = mapping.number % 9 == 0 ? 3 : 1;
		}

		int charsRepeated {};
		while(chars < numeral.end() && std::string_view(chars, chars + 1) == mapping.numeral)
		{
			bool tooManyRepeatableNumerals = ++charsRepeated > 4 && mapping.number != Map[0].number;
			bool tooManyLimitedNumerals	   = charsRepeated > 1 && firstDecimalDigit(mapping.number) == 5;
			if(tooManyRepeatableNumerals || tooManyLimitedNumerals)
				return {};

			++chars;
			number += mapping.number;
		}
	}
	if(chars < numeral.end())
		return {};
	return number;
}

export std::string toUpper(std::string_view str)
{
	std::string upper(str.length(), '\0');
	auto upperPos = upper.begin();
	for(char character : str)
		*upperPos++ = static_cast<char>(std::toupper(character));
	return upper;
}

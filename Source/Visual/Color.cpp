#include "Color.h"


namespace TetraCode {
	Color::Color(bool isActive, int huePair, int brightnessLevel, int number)
		: _isActive(isActive), _huePair(huePair), _brightnessLevel(brightnessLevel), _number(number)
	{}


	bool Color::isActive() const
	{
		return _isActive;
	}


	int Color::huePair() const
	{
		return _huePair;
	}


	int Color::brightnessLevel() const
	{
		return _brightnessLevel;
	}


	int Color::number() const
	{
		return _number;
	}
}



#include "Color.h"


namespace Handmada::TetraCode::Visual {
    Color::Color()
        : _isActive(false), _huePair(0), _brightnessLevel(0), _number(0)
    {
    }


    Color::Color(bool isActive, int huePair, int brightnessLevel, int number)
        : _isActive(isActive), _huePair(huePair), _brightnessLevel(brightnessLevel), _number(number)
    {
    }


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


    bool Color::operator==(const Color& color) const
    {
        return _isActive == color._isActive 
            && _huePair == color._huePair 
            && _brightnessLevel == color._brightnessLevel 
            && _number == color._number;
    }


    bool Color::operator!=(const Color& color) const
    {
        return !operator==(color);
    }
}



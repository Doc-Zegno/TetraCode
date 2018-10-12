#pragma once


namespace TetraCode {
	class Color {
	private:
		bool _isActive;
		int _huePair;
		int _brightnessLevel;
		int _number;

	public:
		Color() = default;
		Color(bool isActive, int huePair, int brightnessLevel, int number);

		bool isActive() const;
		int huePair() const;
		int brightnessLevel() const;
		int number() const;
	};
}

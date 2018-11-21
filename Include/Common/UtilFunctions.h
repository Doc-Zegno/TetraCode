#pragma once


namespace Handmada::TetraCode {
	/// <summary>
	/// Chech whether given value falls within specified range
	/// [start; end)
	/// </summary>
	/// <param name="value">Value to be checked</param>
	/// <param name="start">Range's lower bound (inclusive)</param>
	/// <param name="end">Range's upper bound (exclusive)</param>
	/// <returns>`true` if value is in range and `false` otherwise</returns>
	template<typename T>
	bool isInRange(T value, T start, T end)
	{
		return value >= start && value < end;
	}



	/// <summary>
	/// Check whether given value falls within range [0; end)
	/// </summary>
	/// <param name="value">Value to be checked</param>
	/// <param name="end">Range's upper bound (exclusive)</param>
	/// <returns>`true` if value is in range and `false` otherwise</returns>
	template<typename T>
	bool isInRange(T value, T end)
	{
		return value >= T(0) && value < end;
	}
}

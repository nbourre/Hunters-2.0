#ifndef FRAMECALCULATOR_H
#define FRAMECALCULATOR_H

#include <iostream>
#include <stdio.h>
#include <sfml/system.hpp>

class FrameCalculator
{
private:
	float frameCount;
	sf::Clock frameClock;
	float frameSpeed;
	float speedFactor;
public:
	FrameCalculator();
	virtual ~FrameCalculator();
	void DisplayFrameRate();
	void CalculateFrameRate();
	float GetSpeedFactor();
	void Reset();
protected:
};

#endif // FRAMECALCULATOR_H
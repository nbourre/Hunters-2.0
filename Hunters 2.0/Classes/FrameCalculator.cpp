#include "FrameCalculator.hpp"
#include <SFML/Graphics.hpp>

FrameCalculator::FrameCalculator()
{
	frameClock.restart();
	frameCount = 0;
	frameSpeed = 0.0f;
	speedFactor = 0.0f;
}

FrameCalculator::~FrameCalculator()
{
}

void FrameCalculator::Reset()
{
	frameClock.restart();
	frameCount = 0;
	frameSpeed = 0.0f;
	speedFactor = 0.0f;
}

void FrameCalculator::DisplayFrameRate()
{
	frameCount++;
	if(frameClock.getElapsedTime().asSeconds() >= 1.0f)
	{
		frameSpeed = (float)(1 / frameCount);
		speedFactor = (float)(60 / frameCount);
		std::cout << "FPS: " << frameCount << " TF: " << frameSpeed << " SF: " << speedFactor << std::endl;
		frameCount = 0;
		frameClock.restart();
	}
}

void FrameCalculator::CalculateFrameRate()
{
	frameCount++;
	if(frameClock.getElapsedTime().asSeconds() >= 1.0f)
	{
		frameSpeed = (float)(1 / frameCount);
		speedFactor = (float)(60 / frameCount);
		frameCount = 0;
		frameClock.restart();
	}
}

float FrameCalculator::GetSpeedFactor()
{
	return speedFactor;
}
#pragma once

#include "Framebuffer.h"

float intensity = 2.0f;

float GenerateCaveNoiseValue(CaveNoise c/*, uint8_t index*/, float frequency, byte offset, byte steps, vec3 p)
{
	c.noise.seed += offset;
	c.noise.frequency = frequency;
	float value;
	value = 0.0f;
	//values[1] = 0.0f;
	//values[2] = 0.0f;

	float currentDeg = 1.0f;
	float totalDeg = currentDeg;
	for (byte i = 1; i <= steps; i++)
	{
		value += fnlGetNoise3D(&c.noise, p[0] * i, p[1] * i, p[2] * i) * currentDeg;
		currentDeg *= c.degredation;
		totalDeg += currentDeg;
	}
	value /= totalDeg;

	c.noise.seed -= offset;

	value *= 0.5f;
	value += 0.5f;

	value *= intensity;
	value = value / (value + 1);
	//printf("%f, ", value);

	return value;
}
#include "Inc.h"

float BiasEquation(float value, float bias)
{
	float k = 1.0f - bias;
	k = k * k * k;

	return (value * k) / (value * k - value + 1);
}
#pragma once
#include "Vector3D.h"

class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);
	static float extractScaleTransform(float x, float y, float z);
	static Vector3D convertRadToEuler(float x, float y, float z);
	static Vector3D convertEulerToRad(float x, float y, float z);
	static float converter(float val, float steps);
};




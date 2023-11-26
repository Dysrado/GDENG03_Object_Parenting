#pragma once
#include "GraphicsEngine.h"
#include "Cube.h"


class PhysicsPlane : public Cube
{
public:
	PhysicsPlane(string name, void* shaderByteCode, size_t sizeShader);
	~PhysicsPlane();

};


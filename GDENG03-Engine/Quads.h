#pragma once

#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"

#include "AGameObject.h"


class Quads: public AGameObject
{
public:

	Quads(string name);
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);


private:
	//Buffers
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

	constant cc;

	//Buffer Size
	UINT size_list = 0;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;


};


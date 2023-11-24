#pragma once
#include "GraphicsEngine.h"
#include "AGameObject.h"

class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;

class Cube : public AGameObject
{
public:
	Cube(string name);
	~Cube();


	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);

	void IncrementRot(float offsetIncrease) override;

protected:
	//Buffers
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	constant cc;

	//Buffer Size
	UINT size_list = 0;
	UINT size_index_list = 0;

private:
	

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;



	
	//Vid 2 specification
	float m_rot_x = 0;
	float m_rot_y = 0;
	float m_rot_z = 0;
	

	//Rendering system test case 3:
	Vector3D scale1 = Vector3D(1,  1, 1);
	Vector3D scale2 = Vector3D(2.0f, 0.01f, 2.0f);

	Vector3D translate1 = Vector3D(1, 1, 0);
	Vector3D translate2 = Vector3D(-1, -1, 0);


};


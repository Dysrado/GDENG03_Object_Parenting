#include "PhysicsPlane.h"

#include <list>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"




PhysicsPlane::PhysicsPlane(string name, void* shaderByteCode, size_t sizeShader): Cube(name, shaderByteCode, sizeShader)
{
	typeName = "Physics Cube";
	//TODO: White Version of the Shaders
	Vertex cubeList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,0.95f),  Vector3D(1,0.95f,1)},
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,0.95f,1), Vector3D(1,0.95f,1) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0.95f),  Vector3D(1,1,0.95f) },
		{ Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(1,0.95f,1),Vector3D(1,0.95f,1) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,1,0.95f),  Vector3D(1,0.95f,1) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,0.95f,1),Vector3D(1,0.95f,1) },
		{ Vector3D(-0.5f,0.5f,0.5f),  Vector3D(1,1,0.95f),  Vector3D(1,0.95f,1) },
		{ Vector3D(-0.5f,-0.5f,0.5f),    Vector3D(1,0.95f,1),Vector3D(1,0.95f,1) }
	};


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	indexBuffer = GraphicsEngine::get()->createIndexBuffer();


	size_index_list = ARRAYSIZE(index_list);
	indexBuffer->load(index_list, size_index_list);

	size_list = ARRAYSIZE(cubeList);

	vertexBuffer->load(cubeList, sizeof(Vertex), size_list, shaderByteCode, sizeShader);

	cc.m_time = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(constant));


	this->setScale(10.0f, 0.1f, 10.0f);
	this->setPosition(0, -2.0f, 0);
}

PhysicsPlane::~PhysicsPlane()
{

}

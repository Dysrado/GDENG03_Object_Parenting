#include "Cube.h"

#include <list>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"

Cube::Cube(string name): AGameObject(name)
{
	typeName = "Cube";

	//TODO: Rainbow Version of the Shaders
	Vertex cubeList[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,0,1), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,0,1), Vector3D(0,0.2f,0) }
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

	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	indexBuffer = GraphicsEngine::get()->createIndexBuffer();


	size_index_list = ARRAYSIZE(index_list);
	indexBuffer->load(index_list, size_index_list);

	size_list = ARRAYSIZE(cubeList);

	vertexBuffer->load(cubeList, sizeof(Vertex), size_list, shaderByteCode, sizeShader);


	
	cc.m_time = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	//Matrix4x4 temp;
	//
	//ticks += (deltaTime) * this->speed * 100.0f;
	//float delta = ((sin((ticks / 500.0f)) + 1.0f) / 2.0f) + 0.01f;

	//cc.m_time = (m_rot_x)*this->speed * 100.0f;

	//

	//localMatrix.setIdentity();
	//cc.m_world.setIdentity();
	//temp.setIdentity();
	//temp.setScale(this->getLocalScale());
	//cc.m_world *= temp;
	//localMatrix = cc.m_world;

	//



	////Initial Rotation
	//Matrix4x4 Rot;
	//Rot.setIdentity();

	//temp.setIdentity();
	//temp.setRotationX(this->getLocalRotation().m_x);
	//Rot *= temp;
	//
	//temp.setIdentity();
	//temp.setRotationY(this->getLocalRotation().m_y);
	//Rot *= temp;

	//temp.setIdentity();
	//temp.setRotationZ(this->getLocalRotation().m_z);
	//Rot *= temp;
	//cc.m_world *= Rot;
	//localMatrix = cc.m_world;



	//

	//temp.setIdentity();
	//temp.setTranslation(this->getLocalPosition());
	//cc.m_world *= temp;
	//localMatrix = cc.m_world;

	//

	//// If Parent Exists, then Follow Parent Transform
	//if (parent != nullptr) 
	//{
	//	cc.m_world *= parent->getLocalMatrix(); 
	//}

	//
	//cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();

}

void Cube::draw(int width, int height)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	//set vertex shader and pixel shader for the object
	ShaderNames shaderNames;
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(
		shaderNames.BASE_VERTEX_SHADER_NAME), 
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME)
	);

	if (this->overrideMatrix)
	{
		cc.m_world = localMatrix;
	}

	else
	{
		this->updateLocalMatrix();
		cc.m_world = localMatrix;
	}
	cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)height / (float)width), 0.1f, 100.0f);
	

	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	/*GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);*/

	deviceContext->setConstantBuffer(this->constantBuffer);

	/*GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);*/



	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(indexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}

void Cube::IncrementRot(float offsetIncrease)
{
	this->m_rot_x += offsetIncrease;
	this->m_rot_y += offsetIncrease;
	this->m_rot_z += offsetIncrease;
}

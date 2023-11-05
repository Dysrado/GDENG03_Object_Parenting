#include "Cube.h"

#include <list>

#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"

Cube::Cube(string name, void* shaderByteCode, size_t sizeShader): AGameObject(name)
{
	typeName = "Cube";
	//TODO: White Version of the Shaders
	//Vertex cubeList[] =
	//{
	//	//X - Y - Z
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,0.95f),  Vector3D(1,0.95f,1)},
	//	{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,0.95f,1), Vector3D(1,0.95f,1) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0.95f),  Vector3D(1,1,0.95f) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(1,0.95f,1),Vector3D(1,0.95f,1) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,1,0.95f),  Vector3D(1,0.95f,1) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,0.95f,1),Vector3D(1,0.95f,1) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),  Vector3D(1,1,0.95f),  Vector3D(1,0.95f,1) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),    Vector3D(1,0.95f,1),Vector3D(1,0.95f,1) }
	//};




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


	//TODO: Custom Version of the Shaders Blue to Red
	//Vertex cubeList[] =
	//{
	//	//X - Y - Z
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0)},
	//	{Vector3D(-0.5f,0.5f,-0.5f),     Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,0,1),  Vector3D(1,0,0) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,0,1),  Vector3D(1,0,0) }
	//};

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
}

void Cube::update(float deltaTime)
{
	Matrix4x4 temp;
	
	ticks += (deltaTime) * this->speed * 100.0f;
	float delta = ((sin((ticks / 500.0f)) + 1.0f) / 2.0f) + 0.01f;

	cc.m_time = (m_rot_x)*this->speed * 100.0f;

	//Vector3D currentScale = Vector3D().lerp(scale1, scale2, delta);
	//Vector3D currentTranslate = Vector3D().lerp(translate1, translate2, delta);

	localMatrix.setIdentity();
	cc.m_world.setIdentity();
	temp.setIdentity();
	temp.setScale(this->getLocalScale());
	cc.m_world *= temp;
	localMatrix = cc.m_world;

	//Animation Scale
	/*Matrix4x4 Scaling;
	Scaling.setIdentity();

	temp.setIdentity();
	temp.setScale(currentScale);
	Scaling *= temp;

	cc.m_world *= Scaling;*/



	//Initial Rotation
	Matrix4x4 Rot;
	Rot.setIdentity();

	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().m_x);
	Rot *= temp;
	
	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().m_y);
	Rot *= temp;

	temp.setIdentity();
	temp.setRotationZ(this->getLocalRotation().m_z);
	Rot *= temp;
	cc.m_world *= Rot;
	localMatrix = cc.m_world;



	////Animation Rotation
	//temp.setIdentity();
	//temp.setRotationZ(m_rot_z * speed);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationY(m_rot_y * speed);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationX(m_rot_x * speed);
	//cc.m_world *= temp;

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	cc.m_world *= temp;
	localMatrix = cc.m_world;

	//Translation animation
	/*Matrix4x4 Translate;
	Translate.setIdentity();

	temp.setIdentity();
	temp.setTranslation(currentTranslate);
	Translate *= temp;
	cc.m_world *= Translate;*/

	// If Parent Exists, then Follow Parent Transform
	if (parent != nullptr) 
	{
		cc.m_world *= parent->getLocalMatrix(); //Fundamental problem
		//cc.m_world.getScale().debugPrint();
	}

	/*for(AGameObject* children : childrenList)
	{
		
	}*/
	
	cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();

}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{


	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);
	/*cc.m_proj.setOrthoLH
	(
		(width) / 300.0f,
		(height) / 300.0f,
		-4.0f,
		4.0f
	);*/

	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

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

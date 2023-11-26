#include "Quads.h"

#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include "ShaderLibrary.h"




Quads::Quads(string name) : AGameObject(name)
{
	typeName = "Plane";

	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	Vertex list[] =
	{
		//X - Y - Z

		////Template
		{ Vector3D(-0.5f,0.0f,-0.5f),  Vector3D(0.9f,0.9f,0.9f), Vector3D(0.9f,0.9f,0.9f) }, // POS1
		{ Vector3D(-0.5f,0.0f,0.5f),  Vector3D(0.9f,0.9f,0.9f), Vector3D(0.9f,0.9f,0.9f)}, // POS2
		{ Vector3D(0.5f,0.0f,-0.5f),    Vector3D(0.9f,0.9f,0.9f), Vector3D(0.9f,0.9f,0.9f) },// POS2
		{ Vector3D(0.5f,0.0f,0.5f),   Vector3D(0.9f,0.9f,0.9f), Vector3D(0.9f,0.9f,0.9f) }
	};

	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();

	size_list = ARRAYSIZE(list);

	vertexBuffer->load(list, sizeof(Vertex), size_list, shaderByteCode, sizeShader);



	cc.m_time = 0;

	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(constant));
}

void Quads::update(float deltaTime)
{
	

	Matrix4x4 temp;

	ticks += (EngineTime::getDeltaTime()) * this->speed * 100.0f;
	float delta = ((sin((ticks / 500.0f)) + 1.0f) / 2.0f) + 0.01f;
	cc.m_time = ticks;



	//Start of Converting Model to World view matrix
	localMatrix.setIdentity();
	cc.m_world.setIdentity();
	temp.setIdentity();
	temp.setScale(this->getLocalScale());
	cc.m_world *= temp;
	localMatrix = cc.m_world;



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


	

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	cc.m_world *= temp;
	localMatrix = cc.m_world;

	// If Parent Exists, then Follow Parent Transform
	if (parent != nullptr)
	{
		cc.m_world *= parent->getLocalMatrix();
		//cc.m_world.getScale().debugPrint();
	}

	cc.m_view = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
}

void Quads::draw(int width, int height)
{
	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)height / (float)width), 0.1f, 100.0f);
	/*cc.m_proj.setOrthoLH
	(
		(width) / 300.0f,
		(height) / 300.0f,
		-4.0f,
		4.0f
	);*/

	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	/*GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);*/

	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	ShaderNames shaderNames;
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));
	deviceContext->setConstantBuffer(constantBuffer);

	/*GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);*/

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Quads::setAnimSpeed(float speed)
{
	this->speed = speed;
}



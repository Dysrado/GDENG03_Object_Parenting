#pragma once

#include <cmath>
#include "AppWindow.h"
#include "EngineTime.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "UIManager.h"

//Primitives
#include "Cube.h"
#include "Quads.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"

#include "Toolbar.h"

//Helper
#include "BaseComponentSystem.h"
#include "GameObjectManager.h"
#include "MathUtils.h"
#include "PhysicsSystem.h"

// Shaders
#include "ShaderLibrary.h"
#include "TextureManager.h"

//__declspec(align(16))
//
//struct constant
//{
//	Matrix4x4 m_world;
//	Matrix4x4 m_view;
//	Matrix4x4 m_proj;
//	unsigned int m_time;
//};

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	 
	//Creating Windows and Background
	Window::onCreate();
	GraphicsEngine::get()->init();
	ShaderLibrary::initialize();
	TextureManager::initialize();
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(true);

	
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	//Vertex Shader
	/*GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);*/

	//TODO: Draw create here
	//onCubeCreate(shader_byte_code, size_shader);
	//TODO: STOP DRAWING

	
	
	/*GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();*/

	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//Initialize the Base System
	BaseComponentSystem::getInstance()->initialize();


	SceneCameraHandler::initialize();
	UIManager::initialize(m_hwnd);
	GameObjectManager::initialize();

}

void AppWindow::onUpdate()
{
	m_delta_time = EngineTime::getDeltaTime(); // Engine Time Conversion
	Window::onUpdate();
	InputSystem::getInstance()->update();


	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		bgColor[0], bgColor[1], bgColor[2], 1);

	//VIEWPORT
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//Update All Components;
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();

	SceneCameraHandler::getInstance()->update();
	GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top);

	

	UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	//m_ib->release(); 
	//m_cb->release();
	ShaderLibrary::destroy();
	TextureManager::destroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

	InputSystem::destroy();
	GraphicsEngine::get()->release();


}



void AppWindow::onKeyDown(int key)
{
	//Sir Neil Template
	/*cout << "onkeydown:\n";
	if (InputSystem::getInstance()->isKeyDown('W'))
	{
		cout << "W pressed\n";
	}*/

	if (key == 'W')
	{
		isWPress = true;
	}
	else if (key == 'S')
	{
		isSPress = true;
	}
	


}

void AppWindow::onKeyUp(int key)
{
	/*cout << "onkeyup:\n";
	if (InputSystem::getInstance()->isKeyUp('W'))
	{
		cout << "W released\n";
	}*/

	if (key == 'W')
		isWPress = false;

	if (key == 'S')
		isSPress = false;
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	//Sir Neil Template
	/*cout << " mouse moved: " << deltaPos.getX() << ", " << deltaPos.getY() << "\n";*/

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	//Final
	if (isRightClick) {
		m_rot_x += (deltaPos.getY()) * m_delta_time * 0.3f;
		m_rot_y += (deltaPos.getX()) * m_delta_time * 0.3f;

		//Template
		/*m_rot_x += (deltaPos.getX() - (height / 2.0f)) * m_delta_time * 0.001f;
		m_rot_y += (deltaPos.getY() - (width / 2.0f)) * m_delta_time * 0.001f;*/

	}

	
}

void AppWindow::onLeftMouseDown(const Point deltaPos)
{
	
}

void AppWindow::onLeftMouseUp(const Point deltaPos)
{
	
}

void AppWindow::onRightMouseDown(const Point deltaPos)
{
	
	isRightClick = true;
}

void AppWindow::onRightMouseUp(const Point deltaPos)
{
	
	isRightClick = false;
}

void AppWindow::update()
{
	//constant cc;
	//cc.m_time = ::GetTickCount();

	//m_delta_pos += m_delta_time / 10.0f;
	//if (m_delta_pos > 1.0f)
	//	m_delta_pos = 0;


	//Matrix4x4 temp;

	//m_delta_scale += m_delta_time / 0.55f;

	//

	//cc.m_world.setIdentity();

	//Matrix4x4 world_cam;
	//world_cam.setIdentity();

	//temp.setIdentity();
	//temp.setRotationX(m_rot_x);
	//world_cam *= temp;

	//temp.setIdentity();
	//temp.setRotationY(m_rot_y);
	//world_cam *= temp;


	//Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	//new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	//world_cam.setTranslation(new_pos);

	//m_world_cam = world_cam;


	//world_cam.inverse();




	//cc.m_view = world_cam;
	///*cc.m_proj.setOrthoLH
	//(
	//	(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
	//	(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
	//	-4.0f,
	//	4.0f
	//);*/

	//int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	//int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);


	//cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);


	//m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onImGUICreate()
{
	
	/*if (ImGui::Button("Save"))
		MySaveFunction();
	ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);*/


	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Scene Settings!", NULL, ImGuiWindowFlags_NoResize);           // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Below are the text for configuring the Scene");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Show Demo Window", &isDemoActive);       // Edit bools storing our window open/close state
	

	//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&bgColor);       // Edit 3 floats representing a color


	//TODO Everytime a button is presed change its Text to Resume Animation or Pause Animation
	if (ImGui::Button(animationIndicator.c_str()))                              // Buttons return true when clicked (most widgets return true when edited/activated)
	{
		if (animationIndicator == "Pause Animation")
		{
			isAnimationActive = false;
			animationIndicator = "Resume Animation";
		}
			

		else if (animationIndicator == "Resume Animation")
		{
			isAnimationActive = true;
			animationIndicator = "Pause Animation";
		}
			
	}

	
	ImGui::End();
}

void AppWindow::onImGUIUnityTemplate()
{
}


void AppWindow::onCubeCreate(void* shader_byte_code, size_t size_shader)
{
	//Single Random Instance of the object
	/*Cube* Copy = new Cube("1", shader_byte_code, size_shader);
	Copy->setPosition(Vector3D(MathUtils::randomFloat(-1.0f, 1.0f),
		MathUtils::randomFloat(-1.0f, 1.0f),
		MathUtils::randomFloat(0.0f, 10.0f )));
	Copy->setAnimSpeed(3.0f);
	GameObjectList.push_back(Copy);*/

	////Non Random Instance
	//Cube* First = new Cube("1", shader_byte_code, size_shader);
	//First->setPosition(Vector3D(-1.5f,1.0f,-3.0f));
	//First->setAnimSpeed(20.0f);
	//GameObjectList.push_back(First);

	//Cube* Second = new Cube("1", shader_byte_code, size_shader);
	//Second->setPosition(Vector3D(0, 1.0f, 0));
	//Second->setAnimSpeed(20.0f);
	//GameObjectList.push_back(Second);

	//Cube* Third = new Cube("1", shader_byte_code, size_shader);
	//Third->setPosition(Vector3D(2.6f, 1.0f, 2.0f));
	//Third->setAnimSpeed(20.0f);
	//GameObjectList.push_back(Third);

	//Quads* Plane = new Quads("2", shader_byte_code, size_shader);
	//Plane->setPosition(Vector3D(0, 0, 0));
	////Plane->setRotation(90.0f, 0, 0);
	//Plane->setScale(Vector3D(10.0f, 10.0f, 10.0f));
	//GameObjectList.push_back(Plane);
	//
	
	

	////TODO: Multiple Random Instancing of Cubes
	for (int i = 0; i < 50; i++)
	{
		Cube* Copy = new Cube("1");
		Copy->setPosition(Vector3D(MathUtils::randomFloat(-0.9f, 0.9f),
			MathUtils::randomFloat(-0.9f, 0.9f),
			MathUtils::randomFloat(-0.9f, 0.9f)));
		Copy->setScale(Vector3D(0.25f, 0.25f, 0.25f));
		Copy->setRotation(Vector3D(MathUtils::randomFloat(-180, 180),
			MathUtils::randomFloat(-180, 180),
			MathUtils::randomFloat(-180, 180)));

		float speed = MathUtils::randomFloat(-0.01f, 0.95f) * 10.0f;

		Copy->setAnimSpeed(speed);
		GameObjectList.push_back(Copy);
	}

}



float AppWindow::lerp(float min, float max, float f)
{
	return min * (1.0 - f) + (max * f);
}




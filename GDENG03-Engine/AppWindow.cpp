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
#include "TextureManager.h"
#include "ShaderLibrary.h"


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
	
	InputSystem::initialize();
	InputSystem::getInstance()->addListener(this);
	InputSystem::getInstance()->showCursor(true);

	
	GraphicsEngine::get()->init();
	TextureManager::initialize();
	ShaderLibrary::initialize();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();

	/*void* shader_byte_code = nullptr;
	size_t size_shader = 0;*/

	//Vertex Shader
	//GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	//m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);


	//
	//
	//GraphicsEngine::get()->releaseCompiledShader();

	//GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	//m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	//GraphicsEngine::get()->releaseCompiledShader();

	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);


	//Initialize the Base System
	GameObjectManager::initialize();
	BaseComponentSystem::getInstance()->initialize();
	SceneCameraHandler::initialize();

	UIManager::initialize(m_hwnd);
	
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


	//Components
	BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();

	//GameObject
	SceneCameraHandler::getInstance()->update();
	GameObjectManager::getInstance()->updateAll();
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top);

	

	UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	
	m_swap_chain->release();
	/*m_vs->release();
	m_ps->release();*/

	ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

	InputSystem::destroy();
	GraphicsEngine::get()->release();


}



void AppWindow::onKeyDown(int key)
{
	

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
	

	if (key == 'W')
		isWPress = false;

	if (key == 'S')
		isSPress = false;
}

void AppWindow::onMouseMove(const Point deltaPos)
{
	

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	//Final
	if (isRightClick) {
		m_rot_x += (deltaPos.getY()) * m_delta_time * 0.3f;
		m_rot_y += (deltaPos.getX()) * m_delta_time * 0.3f;

		

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
	
}

void AppWindow::onImGUICreate()
{
	
	


	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Scene Settings!", NULL, ImGuiWindowFlags_NoResize);           // Create a window called "Hello, world!" and append into it.

	ImGui::Text("Below are the text for configuring the Scene");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Show Demo Window", &isDemoActive);       // Edit bools storing our window open/close state
	

	ImGui::ColorEdit3("clear color", (float*)&bgColor);       // Edit 3 floats representing a color


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





float AppWindow::lerp(float min, float max, float f)
{
	return min * (1.0 - f) + (max * f);
}




#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"

//Primitives

#include "AGameObject.h"
#include "Quads.h"


// Dear IMGUI
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	

// Assignment Based Solution
	float lerp(float min, float max, float f);
	//Part 2: Cube


	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point deltaPos);

	virtual void onLeftMouseDown(const Point deltaPos);
	virtual void onLeftMouseUp(const Point deltaPos);

	virtual void onRightMouseDown(const Point deltaPos);
	virtual void onRightMouseUp(const Point deltaPos);
	
	//Tutorial Template
	void update();


	//IMGUI TEMPLATE
	void onImGUICreate();
	void onImGUIUnityTemplate();


private:

	//Graphics Engine
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	
	float m_delta_time;
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;


	bool isRightClick = false;
	bool isSPress = false;
	bool isWPress = false;

	Vector4D backColor = Vector4D();
	

	std::vector<AGameObject*> GameObjectList;

	//ImGUI System
	bool isDemoActive = false;
	bool isAnimationActive = true;
	float bgColor[3] = { 0, 0.3f, 0.4f };
	string animationIndicator = "Pause Animation";

	//UI Manager reference




	
};


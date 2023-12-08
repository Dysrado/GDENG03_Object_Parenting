#include "UIManager.h"

#include "EngineProfiler.h"
#include "GameObjectManager.h"
#include "InspectorWindow.h"
#include "SceneOutliner.h"
#include "ScenePlayOptions.h"
#include "ActionScreen.h"
#include "MaterialScreen.h"

UIManager* UIManager::sharedInstance = nullptr;
UINames uiNames;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{

	sharedInstance = new UIManager(windowHandle);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getDirectD3D11Device(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

	sharedInstance->OnCreateInterface();
}

void UIManager::destroy()
{
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for(int i = 0; i < this->uiList.size(); i++)
	{
		if (uiList[i]->getEnabled())
		{
			uiList[i]->drawUI();
		}
	}

	//Disabling Button Click
	if (ImGui::GetIO().MouseClicked[1]) //Right Clicking
	{
		GameObjectManager::getInstance()->clearSelectedObjectList();
	}


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

void UIManager::setEnabled(String uiName, bool isPopupOpen)
{
	for (int i = 0; i < this->uiList.size(); i++) {
		if (uiList[i]->getName() == uiName)
		{
			uiList[i]->setEnabled(isPopupOpen);
		}
	}
}

AUIScreen* UIManager::findUIByName(String uiName)
{
	for (int i = 0; i < this->uiList.size(); i++) {
		if (uiList[i]->getName() == uiName)
			return uiList[i];
	}

	return NULL;
}

UIManager::UIManager(HWND windowHandle)
{
}

UIManager::~UIManager()
{

}

void UIManager::OnCreateInterface()
{
	Toolbar* toolbar = new Toolbar("New");
	uiList.push_back(toolbar);

	SceneOutliner* sceneOutliner = new SceneOutliner("New");
	uiList.push_back(sceneOutliner);

	InspectorWindow* inspectorWindow = new InspectorWindow("New");
	uiList.push_back(inspectorWindow);

	EngineProfiler* engineProfiler = new EngineProfiler("New");
	uiList.push_back(engineProfiler);

	ScenePlayOptions* scenePlayOptions = new ScenePlayOptions();
	uiList.push_back(scenePlayOptions);

	ActionScreen* actionScreen = new ActionScreen();
	uiList.push_back(actionScreen);

	MaterialScreen* materialScreen = new MaterialScreen(uiNames.MATERIAL_SCREEN, fileDialog);
	materialScreen->setEnabled(false);
	uiList.push_back(materialScreen);
}
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "AppWindow.h"
#include "UINames.h"

//Parts of the Toolbar
#include "Toolbar.h"

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle); 
	static void destroy();

	void drawAllUI();
	void setEnabled(String uiName, bool isPopupOpen);

	static const int WINDOW_WIDTH = 1024; //Based on Window.cpp
	static const int WINDOW_HEIGHT = 768;

	//Boilerplate to be remove

	AUIScreen* findUIByName(String uiName);


private:
	UIManager(HWND windowHandle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;
	ImGui::FileBrowser fileDialog;

	UIList uiList;
	UITable uiTable;


	//BoilerPlate
	void OnCreateInterface();
};


#pragma once
#include "AUIScreen.h"
#include "InspectorWindow.h"
#include "imfilebrowser.h"

class MaterialScreen : public AUIScreen
{
public:
	MaterialScreen(String name, ImGui::FileBrowser fileDialog);
	~MaterialScreen();

	void drawUI() override;

	void linkInspectorScreen(InspectorWindow* inspectorScreen, String materialPath);


private:
	InspectorWindow* inspectorScreen;
	String materialPath;
	Texture* displayTex;
	bool openedExplorerOnce = false;
	ImGui::FileBrowser fileDialog;

	float width = 400.f;
	float height = 450.f;
};


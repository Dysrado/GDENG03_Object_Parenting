#pragma once
#include "UINames.h"
#include <imgui.h>
#include <imfilebrowser.h>
class Toolbar : public AUIScreen
{
public:
	Toolbar(const String name);
	~Toolbar();

	void drawUI() override;

private:
	ImGui::FileBrowser* openFileDialog;
	ImGui::FileBrowser* saveFileDialog;


};


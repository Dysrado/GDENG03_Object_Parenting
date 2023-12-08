#pragma once
#include "AUIScreen.h"
#include <imgui.h>

class ScenePlayOptions : public AUIScreen
{
private:
	ScenePlayOptions();
	~ScenePlayOptions();
	virtual void drawUI() override;

	friend class UIManager;


	bool isPlay = false;
	bool isPaused = false;
};


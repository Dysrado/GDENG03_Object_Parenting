#include "EngineProfiler.h"

#include <sstream>

#include "UIManager.h"
EngineProfiler::EngineProfiler(const String name): AUIScreen(name)
{
}

EngineProfiler::~EngineProfiler()
{
}

void EngineProfiler::drawUI()
{
	float xLength = UIManager::WINDOW_WIDTH * 0.3f;
	float yLength = UIManager::WINDOW_HEIGHT * 0.1f;

	float xPos = UIManager::WINDOW_WIDTH * 0.01f;
	float yPos = UIManager::WINDOW_HEIGHT - (UIManager::WINDOW_HEIGHT * 0.2f);

	float xButtonSize = UIManager::WINDOW_WIDTH * 0.19f;
	float yButtonSize = UIManager::WINDOW_HEIGHT * 0.025f;

	ImGui::Begin("Engine Profiler", NULL, ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove);
	//Window Specificatioon
	ImGui::SetWindowSize(ImVec2(xLength, yLength));
	ImGui::SetWindowPos(ImVec2(xPos, yPos));

	//GameObject Spawning
	ImGui::TextWrapped("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate, ImVec2(xButtonSize, yButtonSize));

	

	ImGui::End();
}

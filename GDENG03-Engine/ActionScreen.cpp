#include "ActionScreen.h"
#include "GameObjectManager.h"
#include "ActionHistory.h"

ActionScreen::ActionScreen() : AUIScreen("ActionScreen")
{
}

ActionScreen::~ActionScreen()
{
}

void ActionScreen::drawUI()
{
	ImGui::Begin("Actions");

	if (ImGui::Button("Undo")) {
		if (ActionHistory::getInstance()->hasRemainingUndoActions()) {
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->undoAction());
		}
	}

	ImGui::SameLine();

	if (ImGui::Button("Redo")) {
		if (ActionHistory::getInstance()->hasRemainingRedoActions()) {
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->redoAction());
		}
	}

	ImGui::End();
}

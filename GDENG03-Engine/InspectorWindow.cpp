#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "UIManager.h"

InspectorWindow::InspectorWindow(const String name) : AUIScreen(name)
{
}

InspectorWindow::~InspectorWindow()
{
}

void InspectorWindow::drawUI()
{
	bool dare = false;
	float copy[3] = { 0,0,0 };

	float xLength = UIManager::WINDOW_WIDTH * 0.2f;
	float yLength = UIManager::WINDOW_HEIGHT * (1.0f - 0.025f);

	float xPos = UIManager::WINDOW_WIDTH - ((UIManager::WINDOW_WIDTH * 0.22f));
	float yPos = UIManager::WINDOW_HEIGHT * 0.025f;

	float xButtonSize = UIManager::WINDOW_WIDTH * 0.19f;
	float yButtonSize = UIManager::WINDOW_HEIGHT * 0.025f;

	ImGui::Begin("Inspector Window", NULL, ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove);
	//Window Specificatioon
	ImGui::SetWindowSize(ImVec2(xLength, yLength));
	ImGui::SetWindowPos(ImVec2(xPos, yPos));


	AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

	if(selectedObject == nullptr)
		ImGui::TextWrapped("No Object Selected, Select an object");

	else
	{
		String text = "Object Selected: ";
		text.append(selectedObject->RetrieveObjName()); // trying obj name over name
		bool isEnable = selectedObject->IsEnabled();
		float t[3] = {
			selectedObject->getLocalPosition().m_x,
			selectedObject->getLocalPosition().m_y,
			selectedObject->getLocalPosition().m_z
		};
		float r[3] = {
			selectedObject->getLocalRotation().m_x,
			selectedObject->getLocalRotation().m_y,
			selectedObject->getLocalRotation().m_z
		};
		float s[3] = {
			selectedObject->getLocalScale().m_x,
			selectedObject->getLocalScale().m_y,
			selectedObject->getLocalScale().m_z
		};

		

		ImGui::TextWrapped(text.c_str());

		if(ImGui::Checkbox("Enabled", &isEnable))
		{
			selectedObject->setEnabled(isEnable);
		};

		ImGui::DragFloat3("Position", t, 0.1f);
		ImGui::DragFloat3("Rotation", r, 0.01f);
		ImGui::DragFloat3("Scale", s, 0.1f);

		selectedObject->setPosition(t[0], t[1], t[2]);
		selectedObject->setRotation(r[0], r[1], r[2]);
		selectedObject->setScale(s[0], s[1], s[2]);

		ImGui::Text("Parent Name: %s", selectedObject->RetrieveParentName().c_str());


		//Button Status
		bool status = GameObjectManager::getInstance()->IsLinkingEnabled();
		if (ImGui::Button("Link"))
		{
			status = true;
			GameObjectManager::getInstance()->SetLinkingEnabled(status);
		}
			

		if (status == true)
		{
			ImGui::SameLine();
			ImGui::Text("Pick GameObject");
		}
		

		if (selectedObject->HasParent())
		{
			if (ImGui::Button("Unlink"))
				GameObjectManager::getInstance()->getSelectedObject()->
				RemoveParent(GameObjectManager::getInstance()->getSelectedObject());
		}
	}
	ImGui::End();
}

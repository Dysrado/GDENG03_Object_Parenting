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


	// Multiple Objects Selected
	GameObjectManager::List selectedObjectsList = GameObjectManager::getInstance()->getSelectedObjectsList();

	if(selectedObjectsList.size() == 0)
	{
		ImGui::TextWrapped("No Object Selected, Select an object");
	}

	else if (selectedObjectsList.size() == 1)
	{
		// Single Object Selected

		AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

		if (selectedObject == nullptr)
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

			if (ImGui::Checkbox("Enabled", &isEnable))
			{
				UpdateChildrenEnableFlag(selectedObjectsList, isEnable);
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
				//Not Enabled
				if(!status)
				{
					GameObjectManager::getInstance()->SetLinkingEnabled(!status);
				}

				//Enabled
				else
				{
					GameObjectManager::getInstance()->SetLinkingEnabled(!status);
				}
				
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

	}


	else if(selectedObjectsList.size() > 1)
	{
		for(int i = 0; i < selectedObjectsList.size(); i++)
		{
			cout << "SELECTED OBJECT: " << selectedObjectsList[i]->RetrieveObjName() << endl;
		}

		// Multiple Objects Selected

		String text = "Object Selected: ";
		text.append("---");

		// In Unity, this is represented by --, but since this is a bool, default true is fine
		bool isEnable = selectedObjectsList[0]->IsEnabled();

		// In Unity, this is represented by --, but since this is a int, using 0 is fine
		float t[3] = {
			0,
			0,
			0
		};
		float r[3] = {
			0,
			0,
			0
		};
		float s[3] = {
			0,
			0,
			0
		};

		ImGui::TextWrapped(text.c_str());

		if (ImGui::Checkbox("Enabled", &isEnable))
		{
			UpdateChildrenEnableFlag(selectedObjectsList, isEnable);
			/*
			for(int i = 0; i < selectedObjectsList.size(); i++)
			{
				int childrenCount = selectedObjectsList[i]->RetrieveAllChildren().size();

				selectedObjectsList[i]->setEnabled(isEnable);
			}
			*/
		};

		ImGui::DragFloat3("Position", t, 0.1f);
		ImGui::DragFloat3("Rotation", r, 0.01f);
		ImGui::DragFloat3("Scale", s, 0.1f);

		for(int i = 0; i < selectedObjectsList.size(); i++)
		{
			selectedObjectsList[i]->setPosition(selectedObjectsList[i]->getLocalPosition().m_x + t[0], selectedObjectsList[i]->getLocalPosition().m_y + t[1], selectedObjectsList[i]->getLocalPosition().m_z + t[2]);
			selectedObjectsList[i]->setRotation(selectedObjectsList[i]->getLocalRotation().m_x + r[0], selectedObjectsList[i]->getLocalRotation().m_y + r[1], selectedObjectsList[i]->getLocalRotation().m_z + r[2]);
			selectedObjectsList[i]->setScale(selectedObjectsList[i]->getLocalScale().m_x + s[0], selectedObjectsList[i]->getLocalScale().m_y + s[1], selectedObjectsList[i]->getLocalScale().m_z + s[2]);
		}

		ImGui::Text("Parent Name: ---");

	}

	ImGui::End();
}

void InspectorWindow::UpdateChildrenEnableFlag(GameObjectManager::List selectedObjectsList, bool isEnable)
{
	for (int i = 0; i < selectedObjectsList.size(); i++)
	{
		int childrenCount = selectedObjectsList[i]->RetrieveAllChildren().size();
		if(childrenCount > 0)
		{
			UpdateChildrenEnableFlag(selectedObjectsList[i]->RetrieveAllChildren(), isEnable);
		}

		selectedObjectsList[i]->setEnabled(isEnable);
	}

}

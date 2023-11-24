#include "Toolbar.h"

#include "Cube.h"
#include "GameObjectManager.h"
#include "UIManager.h"

Toolbar::Toolbar(const string name) : AUIScreen(name)
{
	
}

Toolbar::~Toolbar()
{
}

void Toolbar::drawUI()
{
	//ImGui::ShowDemoWindow(); // Show demo window! :)

	
	if (ImGui::BeginMainMenuBar()) {


		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {
			}
			if (ImGui::MenuItem("Save", "Ctrl+s")) {
			}
			if (ImGui::MenuItem("Open", "Ctrl+o")) {
			}
			if (ImGui::MenuItem("Exit")) {
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game Object"))
		{
			if (ImGui::MenuItem("Create Sphere"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE);
			}

			if (ImGui::MenuItem("Create Cube"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE);
			}

			if (ImGui::MenuItem("Create Textured Cube"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::TEXTURED_CUBE);
			}

			if (ImGui::MenuItem("Create Placeholder Physics Cube"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE);
			}
			
			if (ImGui::MenuItem("Create Plane"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE);
			}

			if (ImGui::MenuItem("Create Placeholder Physics Plane"))
			{
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_PLANE);
			}
			if (ImGui::BeginMenu("Create Light"))
			{
				if (ImGui::MenuItem("Point Light")) {}
				ImGui::EndMenu();
			}
			
			ImGui::EndMenu();

		}

		ImGui::EndMainMenuBar();
	}
		
	
}

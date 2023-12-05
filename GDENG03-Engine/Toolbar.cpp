#include "Toolbar.h"

#include "Cube.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "SceneReader.h"
#include "SceneWriter.h"
Toolbar::Toolbar(const string name) : AUIScreen(name)
{
	saveFileDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	saveFileDialog->SetTitle("Save Scene");
	saveFileDialog->SetTypeFilters({ ".iet" });

	openFileDialog = new ImGui::FileBrowser();
	openFileDialog->SetTitle("Open Scene");
	openFileDialog->SetTypeFilters({ ".iet" });
}

Toolbar::~Toolbar()
{
}

void Toolbar::drawUI()
{

	
	if (ImGui::BeginMainMenuBar()) {


		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) {
				saveFileDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+s")) {
				saveFileDialog->Open();
			}
			if (ImGui::MenuItem("Open", "Ctrl+o")) {
				openFileDialog->Open();
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

		openFileDialog->Display();
		saveFileDialog->Display();
		if (openFileDialog->HasSelected())
		{
			// Full File Path fileDialog.GetSelected().string()
			//std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;

			SceneReader* reader = new SceneReader(openFileDialog->GetSelected().string());
			reader->readFromFile();
			openFileDialog->ClearSelected();
			openFileDialog->Close();
		}

		if (saveFileDialog->HasSelected())
		{
			// Full File Path fileDialog.GetSelected().string()
			//std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
			SceneWriter* file = new SceneWriter();
			file->setDirectory(saveFileDialog->GetSelected().string());
			file->writeToFile();
			saveFileDialog->ClearSelected();
			saveFileDialog->Close();
		}
	}
		
	
}

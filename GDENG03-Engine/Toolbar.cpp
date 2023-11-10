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
			if (ImGui::MenuItem("Create Cube"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();

				


				if (GameObjectManager::getInstance()->getSelectedObject() != nullptr)
				{
					int numOfObjs = GameObjectManager::getInstance()->getAllObjects().size();

					GameObjectManager::getInstance()->getSelectedObject()->AttachChild(GameObjectManager::getInstance()->getAllObjects()[numOfObjs - 1]);
				}
				
			}
			if (ImGui::MenuItem("Create Sphere"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::SPHERE, shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();
			}
			if (ImGui::MenuItem("Create Plane"))
			{
				void* shader_byte_code = nullptr;
				size_t size_shader = 0;
				GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
				GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shader_byte_code, size_shader);
				GraphicsEngine::get()->releaseCompiledShader();

				if (GameObjectManager::getInstance()->getSelectedObject() != nullptr)
				{
					int numOfObjs = GameObjectManager::getInstance()->getAllObjects().size();
					GameObjectManager::getInstance()->getSelectedObject()->AttachChild(GameObjectManager::getInstance()->getAllObjects()[numOfObjs - 1]);
				}
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

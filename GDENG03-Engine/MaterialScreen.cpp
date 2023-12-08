#include "MaterialScreen.h"

#include "TextureManager.h"

MaterialScreen::MaterialScreen(String name, ImGui::FileBrowser fileDialog) : AUIScreen(name)
{
	this->fileDialog = fileDialog;
}

MaterialScreen::~MaterialScreen()
{
}

void MaterialScreen::drawUI()
{
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::Begin("Materials Editor", nullptr, ImGuiWindowFlags_None);
	{
		// Display current texture
		ImGui::SetCursorPosX(50);
		ImGui::Image((displayTex->getShaderResource()), ImVec2(300, 300));

		// Display texture buttons
		if (ImGui::Button("Load Texture", ImVec2(width, 20)))
		{
			fileDialog.Open();

		}
		if (ImGui::Button("Apply", ImVec2(width, 20)))
		{
			this->setEnabled(false);
			this->inspectorScreen->SendResult(this->materialPath);
			this->inspectorScreen = nullptr;
		}
	}
	ImGui::End();

	fileDialog.Display();
	if (fileDialog.HasSelected())
	{
		std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
		this->materialPath = fileDialog.GetSelected().string(); // set material path as selected path

		// replace displayed texture in screen
		std::wstring widestr = std::wstring(materialPath.begin(), materialPath.end());
		const wchar_t* texturePath = widestr.c_str();
		displayTex = TextureManager::getInstance()->createTextureFromFile(texturePath);

		fileDialog.ClearSelected();
	}
}

void MaterialScreen::linkInspectorScreen(InspectorWindow* inspectorScreen, String materialPath)
{
	this->inspectorScreen = inspectorScreen;
	this->materialPath = materialPath;
	std::wstring widestr = std::wstring(materialPath.begin(), materialPath.end());
	const wchar_t* texturePath = widestr.c_str();
	displayTex = TextureManager::getInstance()->createTextureFromFile(texturePath);
}

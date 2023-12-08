#pragma once
#include "GameObjectManager.h"
#include "Texture.h"
#include "UINames.h"

class InspectorWindow: public AUIScreen
{
public:
	InspectorWindow(const String name);
	~InspectorWindow();

	void drawUI() override;

	//Material
	void SendResult(std::string materialPath);

private:
	void UpdateChildrenEnableFlag(GameObjectManager::List selectedObjectsList, bool isEnable);

	//Overloading Component Inspector//
	//Transform
	void UpdateTransformGameObject(AGameObject *aObject);
	void UpdateTransformGameObject(GameObjectManager::List  selectedObjectsList);

	//Rigid Body
	void DisplayRigidBody(AGameObject* aObject);
	void UpdateRigidBody(AGameObject* aObject);

	//Material
	void DisplayMaterials();
	void FormatMatImage();
	std::string materialPath;
	std::string materialName;
	std::string displayTex;
	Texture* materialDisplay;
	bool popupOpen = false;


	//ObjectParenting
	void UpdateParenting(AGameObject* aObject);


};


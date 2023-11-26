#pragma once
#include "GameObjectManager.h"
#include "UINames.h"

class InspectorWindow: public AUIScreen
{
public:
	InspectorWindow(const String name);
	~InspectorWindow();

	void drawUI() override;

private:
	void UpdateChildrenEnableFlag(GameObjectManager::List selectedObjectsList, bool isEnable);

	//Overloading Component Inspector//
	//Transform
	void UpdateTransformGameObject(AGameObject *aObject);
	void UpdateTransformGameObject(GameObjectManager::List  selectedObjectsList);

	//Rigid Body
	void DisplayRigidBody(AGameObject* aObject);

	//ObjectParenting
	void UpdateParenting(AGameObject* aObject);
};


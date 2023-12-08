#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "UIManager.h"
#include "ActionHistory.h"
#include "BaseComponentSystem.h"
#include "MaterialScreen.h"
#include "MathUtils.h"
#include "TexturedCube.h"
#include "ObjectRenderer.h"
#include "TextureManager.h"
#include "PhysicsSystem.h"

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

	//HARD CODED DIMENSION
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

		//Edgecase: After Deletion of gameobject
		if (selectedObject == nullptr)
			ImGui::TextWrapped("No Object Selected, Select an object");

		else
		{
			String text = "Object Selected: ";
			text.append(selectedObject->RetrieveObjName()); // trying obj name over name
			bool isEnable = selectedObject->IsEnabled();

			ImGui::TextWrapped(text.c_str());

			if (ImGui::Checkbox("Enabled", &isEnable))
			{
				UpdateChildrenEnableFlag(selectedObjectsList, isEnable);
			};

			ImGui::SameLine();
			if (ImGui::Button("Delete"))
			{
				GameObjectManager::getInstance()->deleteObject(selectedObject);
			}

			//Transform Component
			UpdateTransformGameObject(selectedObject);

			//Parent Linking/Unlinking
			UpdateParenting(selectedObject);

			//RigidBody
			DisplayRigidBody(selectedObject);

			//Materials
			DisplayMaterials();
		}

	}


	else if(selectedObjectsList.size() > 1)
	{
		/*for(int i = 0; i < selectedObjectsList.size(); i++)
		{
			cout << "SELECTED OBJECT: " << selectedObjectsList[i]->RetrieveObjName() << endl;
		}*/

		// Multiple Objects Selected
		String text = "Object Selected: ";
		text.append("---");

		// In Unity, this is represented by --, but since this is a bool, default true is fine
		bool isEnable = selectedObjectsList[0]->IsEnabled();

		

		ImGui::TextWrapped(text.c_str());

		if (ImGui::Checkbox("Enabled", &isEnable))
		{
			UpdateChildrenEnableFlag(selectedObjectsList, isEnable);
		};

		UpdateTransformGameObject(selectedObjectsList);

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

void InspectorWindow::UpdateTransformGameObject(AGameObject* aObject)
{
	//Transform Properties
	float t[3] = {
		aObject->getLocalPosition().m_x,
		aObject->getLocalPosition().m_y,
		aObject->getLocalPosition().m_z
	};

	Vector3D degreeRotation = MathUtils::convertRadToEuler(
		aObject->getLocalRotation().m_x,
		aObject->getLocalRotation().m_y,
		aObject->getLocalRotation().m_z);
	float r[3] = {
		degreeRotation.m_x,
		degreeRotation.m_y,
		degreeRotation.m_z
	};
	float s[3] = {
		aObject->getLocalScale().m_x,
		aObject->getLocalScale().m_y,
		aObject->getLocalScale().m_z
	};

	if (ImGui::DragFloat3("Position", t, 0.1f)) {
		ActionHistory::getInstance()->startRecordAction(aObject);
		aObject->setPosition(t[0], t[1], t[2]);
		Vector3D radRotation = MathUtils::convertEulerToRad(
			r[0], r[1], r[2]);

		aObject->setRotation(radRotation.m_x, radRotation.m_y, radRotation.m_z);
		aObject->setScale(s[0], s[1], s[2]);
		ActionHistory::getInstance()->endRecordAction(aObject);

		//Update PhysicsComponent
		this->UpdateRigidBody(aObject);
	}
	if (ImGui::DragFloat3("Rotation", r, 5.0f)) {
		ActionHistory::getInstance()->startRecordAction(aObject);
		aObject->setPosition(t[0], t[1], t[2]);

		Vector3D radRotation = MathUtils::convertEulerToRad(
			r[0], r[1], r[2]
		);

		aObject->setRotation(radRotation.m_x, radRotation.m_y, radRotation.m_z);
		aObject->setScale(s[0], s[1], s[2]);
		ActionHistory::getInstance()->endRecordAction(aObject);

		//Update PhysicsComponent
		this->UpdateRigidBody(aObject);
	}
	if (ImGui::DragFloat3("Scale", s, 0.1f)) {
		ActionHistory::getInstance()->startRecordAction(aObject);
		aObject->setPosition(t[0], t[1], t[2]);
		Vector3D radRotation = MathUtils::convertEulerToRad(
			r[0], r[1], r[2]);

		aObject->setRotation(radRotation.m_x, radRotation.m_y, radRotation.m_z);
		aObject->setScale(s[0], s[1], s[2]);
		ActionHistory::getInstance()->endRecordAction(aObject);

		//Update PhysicsComponent
		this->UpdateRigidBody(aObject);
	}
}

void InspectorWindow::UpdateTransformGameObject(GameObjectManager::List selectedObjectsList)
{
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


	ImGui::DragFloat3("Position", t, 0.1f);
	ImGui::DragFloat3("Rotation", r, 0.01f);
	ImGui::DragFloat3("Scale", s, 0.1f);

	for (int i = 0; i < selectedObjectsList.size(); i++)
	{
		selectedObjectsList[i]->setPosition(selectedObjectsList[i]->getLocalPosition().m_x + t[0], selectedObjectsList[i]->getLocalPosition().m_y + t[1], selectedObjectsList[i]->getLocalPosition().m_z + t[2]);
		selectedObjectsList[i]->setRotation(selectedObjectsList[i]->getLocalRotation().m_x + r[0], selectedObjectsList[i]->getLocalRotation().m_y + r[1], selectedObjectsList[i]->getLocalRotation().m_z + r[2]);
		selectedObjectsList[i]->setScale(selectedObjectsList[i]->getLocalScale().m_x + s[0], selectedObjectsList[i]->getLocalScale().m_y + s[1], selectedObjectsList[i]->getLocalScale().m_z + s[2]);
	}
}

void InspectorWindow::DisplayRigidBody(AGameObject* aObject)
{
	bool isComponentActive = false;
	PhysicsComponent* pComponent = (PhysicsComponent*)aObject->
	findComponentByName("Physics_Component" + aObject->RetrieveObjName());

	if (pComponent == nullptr)
	{
		ImGui::Text("Rigid Body: None");
		if(ImGui::Button("Add RigidBody"))
		{
			PhysicsComponent* component;
			if(aObject->getObjectType() == AGameObject::PHYSICS_PLANE)
				component = new PhysicsComponent("Physics_Component" + aObject->RetrieveObjName(), aObject, BodyType::STATIC);

			else
				component = new PhysicsComponent("Physics_Component" + aObject->RetrieveObjName(), aObject, BodyType::DYNAMIC);

			aObject->attachComponent(component);
		}
	}

	else
	{
		bool isPEnabled = pComponent->IsEnable();

		RigidBody* rigidBody = pComponent->getRigidBody();
		bool isStatic = rigidBody->getType() == BodyType::STATIC;
		bool isGravityEnabled = rigidBody->isGravityEnabled();
		float mass = rigidBody->getMass();
		
		float forceVector[3] = {
			pComponent->forceVector->x,
			pComponent->forceVector->y,
			pComponent->forceVector->z};


		ImGui::Text("Rigid Body:" );
		if(ImGui::Button("Detach"))
		{
			aObject->detachComponent(pComponent);
			BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(pComponent);
			delete pComponent;
			return;
		}
		ImGui::Checkbox("Is Enabled", &isPEnabled);
		ImGui::Checkbox("Is Static", &isStatic);
		ImGui::Checkbox("Enabled Gravity", &isGravityEnabled);

		ImGui::Text("Set Mass:");
		ImGui::DragFloat("kg", &mass, 0.5f, 1.0f, 1000000.0f);
		ImGui::DragFloat3("Apply Force Vector", forceVector, 0.1f);
		pComponent->forceVector->x = forceVector[0];
		pComponent->forceVector->y = forceVector[1];
		pComponent->forceVector->z = forceVector[2];
		if(ImGui::Button("Apply Force"))
		{
			//Do Something
			Vector3 finalForce;
			finalForce.x = (pComponent->forceVector->x / mass);
			finalForce.y = (pComponent->forceVector->y / mass);
			finalForce.z = (pComponent->forceVector->z / mass);
			rigidBody->setLinearVelocity(finalForce);
			
		}


		pComponent->SetEnable(isPEnabled);
		if (isStatic)
			rigidBody->setType(BodyType::STATIC);
		else
			rigidBody->setType(BodyType::DYNAMIC);

		rigidBody->enableGravity(isGravityEnabled);
		rigidBody->setMass(mass);

	}

	
}

void InspectorWindow::UpdateRigidBody(AGameObject* aObject)
{
	bool isComponentActive = false;
	PhysicsComponent* pComponent = (PhysicsComponent*)aObject->findComponentByName("Physics_Component" + aObject->RetrieveObjName());
	if (pComponent != nullptr)
	{
		
		float mass = pComponent->getRigidBody()->getMass();
		bool isGravityEnabled = pComponent->getRigidBody()->isGravityEnabled();
		BodyType objType = pComponent->getRigidBody()->getType();

		BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(pComponent);
		pComponent->getOwner()->detachComponent(pComponent);
		aObject->attachComponent(new PhysicsComponent("Physics_Component" + aObject->RetrieveObjName(),
			aObject, objType));
		

		PhysicsComponent* newPObject = (PhysicsComponent*)aObject->findComponentByName("Physics_Component" + aObject->RetrieveObjName());
		newPObject->getRigidBody()->setMass(mass);
		newPObject->getRigidBody()->enableGravity(isGravityEnabled);
		delete pComponent;

	}

}

void InspectorWindow::DisplayMaterials()
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();

	int BUTTON_WIDTH = 200;
	int BUTTON_HEIGHT = 20;

	if (gameObjManager->getSelectedObject() != nullptr)
	{
		if (gameObjManager->getSelectedObject()->getObjectType() != AGameObject::TEXTURED_CUBE)
		{
			return;
		}

		TexturedCube* texturedObj = static_cast<TexturedCube*>(gameObjManager->getSelectedObject());
		this->materialPath = texturedObj->getRenderer()->getMaterialPath();
		this->FormatMatImage();
		ImGui::SetCursorPosX(50);
		ImGui::Image(static_cast<void*>(materialDisplay->getShaderResource()), ImVec2(100, 100));

		// replace '\' with '/'
		std::replace(materialPath.begin(), materialPath.end(), '\\', '/');

		//Get file name from path
		std::string outputName;
		for (int i = materialPath.length(); i > 0; i--)
		{
			if (materialPath[i] != '/')
			{
				outputName.insert(outputName.begin(), materialPath[i]);
			}
			else
			{
				i = 0;
			}
		}

		materialName = outputName;
		std::string displayText = "Material: ";
		displayText.append(materialName);
		ImGui::Text(displayText.c_str());
		if (ImGui::Button("Add Material", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT)))
		{
			popupOpen = !popupOpen;
			std::cout << "Popup Open: " << popupOpen << std::endl;
			UINames uiNames;
			MaterialScreen* materialScreen = static_cast<MaterialScreen*>(UIManager::getInstance()->findUIByName(uiNames.MATERIAL_SCREEN));
			materialScreen->linkInspectorScreen(this, materialPath);
			UIManager::getInstance()->setEnabled(uiNames.MATERIAL_SCREEN, popupOpen);
		}
	}
}

void InspectorWindow::FormatMatImage()
{
	// covert to wchar
	std::string textureString = this->materialPath;
	std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
	const wchar_t* texturePath = widestr.c_str();
	this->materialDisplay = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
}

void InspectorWindow::SendResult(std::string materialPath)
{
	GameObjectManager* gameObjManager = GameObjectManager::getInstance();
	TexturedCube* texturedObj = static_cast<TexturedCube*>(gameObjManager->getSelectedObject());
	texturedObj->getRenderer()->setRenderer(materialPath);
	this->popupOpen = false;
}

void InspectorWindow::UpdateParenting(AGameObject* aObject)
{
	ImGui::Text("Parent Name: %s", aObject->RetrieveParentName().c_str());


	//Button Status
	bool status = GameObjectManager::getInstance()->IsLinkingEnabled();
	if (ImGui::Button("Link"))
	{

		if (!status) { //Not Enabled
			GameObjectManager::getInstance()->SetLinkingEnabled(!status);
		}

		else { //Enabled
			GameObjectManager::getInstance()->SetLinkingEnabled(!status);
		}

	}


	if (status == true)
	{
		ImGui::SameLine();
		ImGui::Text("Pick GameObject");
	}


	if (aObject->HasParent())
	{
		if (ImGui::Button("Unlink"))
			GameObjectManager::getInstance()->getSelectedObject()->
			RemoveParent(GameObjectManager::getInstance()->getSelectedObject());
	}
}


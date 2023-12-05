#include "InspectorWindow.h"

#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "UIManager.h"
#include "ActionHistory.h"

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
	float r[3] = {
		aObject->getLocalRotation().m_x,
		aObject->getLocalRotation().m_y,
		aObject->getLocalRotation().m_z
	};
	float s[3] = {
		aObject->getLocalScale().m_x,
		aObject->getLocalScale().m_y,
		aObject->getLocalScale().m_z
	};

	if (ImGui::DragFloat3("Position", t, 0.1f)) {
		ActionHistory::getInstance()->startRecordAction(aObject);
		aObject->setPosition(t[0], t[1], t[2]);
		aObject->setRotation(r[0], r[1], r[2]);
		aObject->setScale(s[0], s[1], s[2]);
		ActionHistory::getInstance()->endRecordAction(aObject);
	}
	if (ImGui::DragFloat3("Rotation", r, 0.01f)) {
		ActionHistory::getInstance()->startRecordAction(aObject);
		aObject->setPosition(t[0], t[1], t[2]);
		aObject->setRotation(r[0], r[1], r[2]);
		aObject->setScale(s[0], s[1], s[2]);
		ActionHistory::getInstance()->endRecordAction(aObject);
	}
	if (ImGui::DragFloat3("Scale", s, 0.1f)) {
		ActionHistory::getInstance()->startRecordAction(aObject);
		aObject->setPosition(t[0], t[1], t[2]);
		aObject->setRotation(r[0], r[1], r[2]);
		aObject->setScale(s[0], s[1], s[2]);
		ActionHistory::getInstance()->endRecordAction(aObject);
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
	PhysicsComponent* pComponent = (PhysicsComponent*)aObject->findComponentByName("Physics_Component");

	if (pComponent == nullptr)
	{
		ImGui::Text("Rigid Body: None");
		if(ImGui::Button("Add RigidBody"))
		{
			PhysicsComponent* component = new PhysicsComponent("Physics_Component", aObject, BodyType::STATIC);
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
			
			rigidBody->applyLocalForceAtCenterOfMass(*pComponent->forceVector);
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


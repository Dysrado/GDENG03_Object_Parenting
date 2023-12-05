#include "GameObjectManager.h"
#include <iostream>

#include "AGameObject.h"

//Primitives
#include "Cube.h"
#include "Quads.h"
#include "PhysicsPlane.h"

//Components
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "TexturedCube.h"
#include "EditorAction.h"


GameObjectManager* GameObjectManager::sharedInstance = nullptr;

void GameObjectManager::applyEditorAction(EditorAction* action)
{
	AGameObject* object = this->findObjectByName(action->getOwnerName());
	if (object != NULL) {
		//re-apply state
		object->recomputeMatrix(action->getStoredMatrix().getFloatArray());
		object->setPosition(action->getStorePos());
		object->setRotation(action->getStoredOrientation().x, action->getStoredOrientation().y, action->getStoredOrientation().z);
		object->setScale(action->getStoredScale());

	}
}

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager;
}

void GameObjectManager::destroy()
{
	sharedInstance->aList.clear();
	sharedInstance->aTable.clear();

}

AGameObject* GameObjectManager::findObjectByName(String name)
{
	if(aTable[name] == nullptr)
	{
		std::cout << "Faied to Find Object" << std::endl;
		return nullptr;
	}

	return aTable[name];
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return aList;
}

int GameObjectManager::activeObjects()
{
	//TODO: Retrieve the total number of object
	return aList.size();
}

void GameObjectManager::updateAll()
{
	for(AGameObject* gameobject: aList)
	{
		if(gameobject->IsEnabled())
			gameobject->update(EngineTime::getDeltaTime());
	}
}

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight)
{
	for (AGameObject* gameobject : aList)
	{
		if(gameobject->IsEnabled())
			gameobject->draw(viewportHeight, viewportWidth);
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	
	String Key = gameObject->RetrieveName();
	int i = 0;
	while (aTable[Key] != nullptr)
	{
		i++;
		Key = gameObject->RetrieveName();
		Key.append(std::to_string(i));
	}
	aTable[Key] = gameObject;
	aList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	switch (type)
	{
		case PrimitiveType::CUBE:
		{
			string objName = "Cube";
			if (cubeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(cubeCount));
				objName.append(") ");
			}

			Cube* cube = new Cube(objName);
			addObject((AGameObject*)cube);

			cubeCount++;
		}

		break;

		case PrimitiveType::PHYSICS_CUBE:
		{
			for (int i = 0; i < 10; i++)
			{
				string objName = "Physics Cube";
				if (pCubeCount != 0)
				{
					objName.append(" (");
					objName.append(std::to_string(pCubeCount));
					objName.append(") ");
				}


				Cube* cube = new Cube("Cube_Physics");
				cube->setPosition(0, 5.0f, 0);
				this->addObject(cube);

				

				// add the Physics Component - External Method
				string componentName = "Physics_Component";
				PhysicsComponent* component = new PhysicsComponent(componentName, cube, BodyType::DYNAMIC);
				cube->attachComponent(component);
			}
		}
		break;
		
		case PrimitiveType::PLANE:
		{
			string objName = "Plane";
			if (planeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(planeCount));
				objName.append(") ");
			}

			Quads* quads = new Quads(objName);
			addObject((AGameObject*)quads);

			planeCount++;
		}
		break;


		case PrimitiveType::PHYSICS_PLANE:
		{
			string objName = "Physics Plane";
			if (planeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(planeCount));
				objName.append(") ");
			}

			PhysicsPlane* plane = new PhysicsPlane(objName);
			this->addObject(plane);

			// add the Physics Component
			string componentName = "Physics_Component";
			PhysicsComponent* component = new PhysicsComponent(componentName, plane, BodyType::STATIC);
			plane->attachComponent(component);

		}
		break;


		case PrimitiveType::SPHERE:
		{std::cout << "Choose Sphere" << std::endl;}
		break;


		case PrimitiveType::TEXTURED_CUBE:
		{
			string objName = "Textured Cube";
			if (cubeCount != 0)
			{
				objName.append(" (");
				objName.append(std::to_string(cubeCount));
				objName.append(") ");
			}

			TexturedCube* cube = new TexturedCube(objName);
			addObject((AGameObject*)cube);

			cubeCount++;
		}
		break;
	}
	
}


void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	
	//First Method
	/*for(int i = 0; i < aList.size(); i++)
	{
		if(aList[i] == gameObject)
		{
			
			delete(aList[i]);
			aList.shrink_to_fit();
			break;
		}
	}*/

	// 2nd Method
	this->aTable.erase(gameObject->name);

	int index = -1;
	for (int i = 0; i < this->aList.size(); i++) {
		if (this->aList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->aList.erase(this->aList.begin() + index);
	}

	if (gameObject == this->selectedObject)
		this->selectedObject = nullptr;

	// actual deletion of the pointer causes an issue for some reason
	//delete gameObject;
}

void GameObjectManager::deleteAllObjects()
{
	for (int i = 0; i < aList.size(); i++)
	{
		delete aList[i];
	}

	selectedObject = nullptr;
	aList.clear();
	aTable.clear();
}

void GameObjectManager::clearSelectedObjectList()
{
	selectedObject = nullptr;
	selectedObjectsList.clear();
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject, bool isMultiselect)
{
	String Key = gameObject->RetrieveName();
	int i = 0;
	while (aTable[Key] != gameObject)
	{
		i++;
		Key = gameObject->RetrieveName();
		Key.append(std::to_string(i));
	}
	selectedObject = aTable[Key];


	if (!isMultiselect)
		selectedObjectsList.clear();

	// For multiple selection
	bool isDuplicate = false;
	for(int i = 0; i < selectedObjectsList.size(); i++)			// check if object is already selected
	{
		if (selectedObjectsList[i]->RetrieveObjName() == gameObject->RetrieveObjName())
			isDuplicate = true;
	}

	if(!isDuplicate)
		selectedObjectsList.push_back(selectedObject);
}

bool GameObjectManager::isSelectedOnObjectList(AGameObject* game_object)
{
	for(AGameObject* AObject : selectedObjectsList)
	{
		if (AObject == game_object)
			return true;
	}

	return false;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return selectedObject;
}

GameObjectManager::List GameObjectManager::retrieveBaseParentObject()
{
	GameObjectManager::List allParentObject;

	for(AGameObject* object : aList)
	{
		if (!object->HasParent())
			allParentObject.push_back(object);
	}

	return allParentObject;
}

GameObjectManager::List GameObjectManager::getSelectedObjectsList()
{
	return selectedObjectsList;
}

bool GameObjectManager::IsLinkingEnabled()
{
	return isLinkEnable;
}

void GameObjectManager::SetLinkingEnabled(bool flag)
{
	isLinkEnable = flag;
}

void GameObjectManager::saveEditStates()
{
	for (int i = 0; i < this->aList.size(); i++) {
		this->aList[i]->saveEditState();
	}
}

void GameObjectManager::restoreEditStates()
{
	for (int i = 0; i < this->aList.size(); i++) {
		this->aList[i]->restoreEditState();
	}
}

void GameObjectManager::createObjectFromFile(std::string objectName, AGameObject::PrimitiveType objectType, Vector3D position, Vector3D rotation, Vector3D scale, float mass, bool isGravityEnabled)
{
	if (objectType == AGameObject::PrimitiveType::CUBE) {
		Cube* cube = new Cube(objectName);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		addObject(cube);
	}

	else if (objectType == AGameObject::PrimitiveType::PLANE) {
		Quads* plane = new Quads(objectName);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		addObject(plane);
	}

	else if (objectType == AGameObject::PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube(objectName);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		//cube->getRenderer()->setRenderer(path);

		/*String textureString = path;
		std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
		const wchar_t* texturePath = widestr.c_str();

		static_cast<TexturedCube*>(cube)->getRenderer()->setTexture(TextureManager::getInstance()->createTextureFromFile(texturePath));*/
		addObject(cube);
	}

	else if (objectType == AGameObject::PrimitiveType::PHYSICS_CUBE) {
		Cube* cube = new Cube(objectName);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		cube->attachComponent(new PhysicsComponent("Physics_Component", cube, BodyType::DYNAMIC));
		static_cast<PhysicsComponent*>(cube->findComponentByName("Physics_Component"))->getRigidBody()->setMass(mass);
		static_cast<PhysicsComponent*>(cube->findComponentByName("Physics_Component"))->getRigidBody()->enableGravity(isGravityEnabled);
		addObject(cube);
	}

	else if (objectType == AGameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(objectName);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		plane->attachComponent(new PhysicsComponent("Physics_Component", plane, BodyType::KINEMATIC));

		addObject(plane);
	}
}





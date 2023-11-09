#include "GameObjectManager.h"
#include <iostream>

#include "AGameObject.h"

//Primitives
#include "Cube.h"
#include "Quads.h"

GameObjectManager* GameObjectManager::sharedInstance = nullptr;

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

void GameObjectManager::renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader,
	PixelShader* pixels_shader)
{
	for (AGameObject* gameobject : aList)
	{
		if(gameobject->IsEnabled())
			gameobject->draw(viewportHeight, viewportWidth, vertexShader, pixels_shader);
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
	//std::pair<String, AGameObject*> pair(Key, gameObject);
	aTable[Key] = gameObject;
	aList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader)
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

			Cube* cube = new Cube(objName, shaderByteCode, sizeShader);
			addObject((AGameObject*)cube);

			cubeCount++;
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

			Quads* quads = new Quads(objName, shaderByteCode, sizeShader);
			addObject((AGameObject*)quads);

			planeCount++;
		}
		break;

		case PrimitiveType::SPHERE:
		{std::cout << "Choose Sphere" << std::endl;}
		break;

	}
	
}


void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	
	//First Method
	for(int i = 0; i < aList.size(); i++)
	{
		if(aList[i] == gameObject)
		{
			//Potential Issue for the way how it destroyed
			//aTable.erase(pair);
			delete(aList[i]);
			aList.shrink_to_fit();
			break;
		}
	}

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





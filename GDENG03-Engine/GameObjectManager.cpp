#include "GameObjectManager.h"
#include <iostream>

#include "AGameObject.h"

//Primitives
#include "Cube.h"
#include "PhysicsPlane.h"
#include "MathUtils.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "Quads.h"
#include "TexturedCube.h"

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
	//std::pair<String, AGameObject*> pair(Key, gameObject);
	aTable[Key] = gameObject;
	aList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	switch (type)
	{
		case PrimitiveType::CUBE:
		{
			Cube* cube = new Cube("Cube");
			addObject((AGameObject*)cube);
		}
		break;

		case PrimitiveType::PHYSICS_CUBE:
		{
			for (int i = 0; i < 2; i++)
			{
				Cube* cube = new Cube("Cube_Physics");
				cube->setPosition(MathUtils::randomFloat(-0.8f, 0.8f) ,
					2.0f, 
					MathUtils::randomFloat(-0.8f, 0.8f));
				cube->setRotation(0, MathUtils::randomInt(0, 180), 0);
				cube->setScale(1.0f, 1.0f, 1.0f);
				this->addObject(cube);

				// add the Physics Component
				string componentName = "Physics_Component" + cube->RetrieveName();
				PhysicsComponent* component = new PhysicsComponent(componentName, cube, BodyType::DYNAMIC);
				
				//component->getRigidBody()->setAngularDamping(10.0f);
				component->getRigidBody()->setLinearDamping(0.60f);
			}
		}
		break;

		case PrimitiveType::PLANE:
		{
			Quads* quads = new Quads("Plane");
			addObject((AGameObject*)quads);
		}
		break;

		case PrimitiveType::PHYSICS_PLANE:
		{
			PhysicsPlane* plane = new PhysicsPlane("Plane_Physics");
			this->addObject(plane);

			// add the Physics Component
			string componentName = "Physics_Component" + plane->RetrieveName();
			PhysicsComponent* component = new PhysicsComponent(componentName, plane, BodyType::STATIC);
			
			
		}
		break;


		case PrimitiveType::SPHERE:
		{std::cout << "Choose Sphere" << std::endl;}
		break;

		case PrimitiveType::TEXTURED_CUBE:
		{
			TexturedCube* cube = new TexturedCube("Cube_Textured");
			cube->setPosition(0.0f, 0.0f, 0.0f);
			cube->setScale(1.0f, 1.0f, 1.0f);
			this->addObject(cube);
			break;
		}

	}
	
}


void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	/*for (auto it = aList.begin(); it != aList.end();)
	{
		if (it->first % 2 != 0)
			it = c.erase(it);
		else
			++it;
	}*/

	

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

	

	
	//for (AGameObject* aObject : aList)
	//{
	//	if (aObject == gameObject)
	//	{
	//		//Potential Issue for the way how it destroye
	//		aList.erase(aObject);
	//	}
	//}
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
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
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return selectedObject;
}

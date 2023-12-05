#include "SceneWriter.h"
#include "GameObjectManager.h"
#include <fstream>
#include "StringUtils.h"
#include "TexturedCube.h"
//#include "ObjectRenderer.h"
#include "PhysicsComponent.h"


void SceneWriter::setDirectory(String directory)
{
	this->directory = directory;
}

void SceneWriter::writeToFile()
{
	String fileDir = this->directory + ".iet";
	if (this->directory.find(".iet") != String::npos) 
	{
		fileDir = this->directory;
	}

	std::ofstream sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected file directory " << fileDir << "\n";

	GameObjectManager::List allObjects = GameObjectManager::getInstance()->getAllObjects();

	for (int i = 0; i < allObjects.size(); i++) 
	{
		sceneFile << allObjects[i]->RetrieveName() << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();
		float mass = 0;
		String hasRigidbody = "0";
		bool isGravityEnabled = true;

		if (allObjects[i]->findComponentByName("Physics_Component")) 
		{
			mass = static_cast<PhysicsComponent*>(allObjects[i]->findComponentByName("Physics_Component"))->getRigidBody()->getMass();
			hasRigidbody = "1";
			isGravityEnabled = static_cast<PhysicsComponent*>(allObjects[i]->findComponentByName("Physics_Component"))->getRigidBody()->isGravityEnabled();
		}


			
		sceneFile << "Type:|" << allObjects[i]->getObjectType() << "|" << hasRigidbody << "|" << mass << "|"  << isGravityEnabled << "|" << std::endl;
		sceneFile << "Position:|"	<< position.m_x	<< "|" << position.m_y << "|"	<< position.m_z	<< "|" << std::endl;
		sceneFile << "Rotation:|"	<< rotation.m_x	<< "|" << rotation.m_y << "|"	<< rotation.m_z	<< "|" << std::endl;
		sceneFile << "Scale:|"		<< scale.m_x		<< "|" << scale.m_y << "|"		<< scale.m_z		<< "|" << std::endl;
	}
	sceneFile.close();
}

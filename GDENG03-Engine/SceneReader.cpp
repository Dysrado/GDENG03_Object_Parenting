#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "AGameObject.h"
#include "StringUtils.h"

typedef std::fstream FileReader;
SceneReader::SceneReader(String directory)
{
	this->directory = directory;
}

SceneReader::~SceneReader()
{
}

void SceneReader::readFromFile()
{
	String fileDir = this->directory + ".iet";
	if (this->directory.find(".iet") != String::npos) {
		fileDir = this->directory;
	}
	GameObjectManager::getInstance()->deleteAllObjects();
	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	String readLine;

	String objectName;
	AGameObject::PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	String hasRigidbody = "0";
	float mass = 0;
	bool isGravityEnabled = true;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) { // Type
			std::vector stringSplit = StringUtils::split(readLine, '|');
			objectType = (AGameObject::PrimitiveType)std::stoi(stringSplit[1]);
			hasRigidbody = stringSplit[2];
			mass = std::stof(stringSplit[3]);
			isGravityEnabled = std::stof(stringSplit[4]);
			if (objectType == AGameObject::PrimitiveType::CUBE && hasRigidbody == "1") objectType = AGameObject::PrimitiveType::PHYSICS_CUBE;
			if (objectType == AGameObject::PrimitiveType::PLANE && hasRigidbody == "1")objectType = AGameObject::PrimitiveType::PHYSICS_PLANE;
			index++;
		}
		else if (index == 2) { // Position
			std::vector stringSplit = StringUtils::split(readLine, '|');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 3) { // Rotation
			std::vector stringSplit = StringUtils::split(readLine, '|');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4) { // Scale
			std::vector stringSplit = StringUtils::split(readLine, '|');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index = 0;

			//std::cout << "Values: " << objectName << objectType << position.m_x << rotation.m_x << scale.m_x << mass << isGravityEnabled << "\n";
			GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, mass, isGravityEnabled);
		}
	}
	sceneFile.close();
}


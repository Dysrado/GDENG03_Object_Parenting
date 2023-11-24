#pragma once
#include <string>
#include <unordered_map>
#include <vector>


class Quads;
//Primitive
class Cube;
class PixelShader;
class VertexShader;
class AGameObject;

//Graphics



class GameObjectManager
{
public:
	typedef std::string String;
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<String, AGameObject*> HashTable;

	enum PrimitiveType
	{
		CUBE,
		PHYSICS_CUBE,
		PLANE,
		PHYSICS_PLANE,
		TEXTURED_CUBE,
		SPHERE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	List getAllObjects();
	int activeObjects();

	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void deleteObject(AGameObject* gameObject);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

private:
	static GameObjectManager* sharedInstance;

	HashTable aTable;
	List aList;
	AGameObject* selectedObject = nullptr;


	


};


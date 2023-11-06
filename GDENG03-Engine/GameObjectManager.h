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
		PLANE,
		SPHERE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(String name);
	List getAllObjects();
	int activeObjects();

	void updateAll();
	void renderAll(int viewportWidth, int viewportHeight, VertexShader* vertexShader, PixelShader* pixels_shader);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(AGameObject* gameObject);

	void setSelectedObject(AGameObject* gameObject);
	void addToSelectedObject(AGameObject* gameObject);

	AGameObject* getSelectedObject();
	List retrieveBaseParentObject();

	bool IsLinkingEnabled();
	void SetLinkingEnabled(bool flag);

private:
	static GameObjectManager* sharedInstance;

	HashTable aTable;
	List aList;
	AGameObject* selectedObject = nullptr;
	

	// Object counts
	int cubeCount = 0;
	int planeCount = 0;

	//Object Parenting
	bool isLinkEnable = false;
	
};


#pragma once
#include <string>
#include <unordered_map>
#include <vector>


class EditorAction;
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

	void applyEditorAction(EditorAction* action);

	enum PrimitiveType
	{
		CUBE,
		PHYSICS_CUBE,
		PLANE,
		PHYSICS_PLANE,
		SPHERE,
		TEXTURED_CUBE
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

	void clearSelectedObjectList();
	void setSelectedObject(AGameObject* gameObject, bool isMultiSelect);
	bool isSelectedOnObjectList(AGameObject* game_object);

	AGameObject* getSelectedObject();
	List retrieveBaseParentObject();
	List getSelectedObjectsList();

	bool IsLinkingEnabled();
	void SetLinkingEnabled(bool flag);

	void saveEditStates();
	void restoreEditStates();


private:
	static GameObjectManager* sharedInstance;

	HashTable aTable;
	List aList;
	AGameObject* selectedObject = nullptr;
	List selectedObjectsList;

	// Object counts
	int cubeCount = 0;
	int planeCount = 0;
	int pCubeCount = 0;
	int pPlaneCount = 0;

	//Object Parenting
	bool isLinkEnable = false;
	
};


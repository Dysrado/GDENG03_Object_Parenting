#pragma once
#include <string>
#include <vector>

#include "Matrix4x4.h"
#include "Vector3D.h"
#include "EngineTime.h"

__declspec(align(16))

struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};


using namespace std;
class VertexShader;
class PixelShader;

class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();
	Vector3D getParentLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();
	Vector3D getParentLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();
	Vector3D getParentLocalRotation();

	virtual void IncrementRot(float offset);

	void SetParent(AGameObject* reference);
	void RemoveParent(AGameObject* reference);
	void AttachChild(AGameObject* reference);
	void RemoveChild(AGameObject* reference);
	bool HasParent();
	bool containSameParent(AGameObject* reference);
	std::vector<AGameObject* > RetrieveAllChildren();

	string RetrieveName();
	string RetrieveObjName();
	string RetrieveParentName();
	void setEnabled(bool flag);
	bool IsEnabled();

	Matrix4x4 getLocalMatrix();
	Matrix4x4 computeLocalMatrix();
	Matrix4x4 computeWorldMatrix();

	//placeholder function - cant think of an optimized way of deleting
	bool isSameGameObject(AGameObject* reference);
	
private:
	string name;
	

	Vector3D localRotation;
	Vector3D localPosition;
	Vector3D localScale;
	bool isEnabled = true;

protected:
	Matrix4x4 localMatrix;
	string typeName;

	AGameObject* parent;
	vector<AGameObject*> childrenList;


};


#pragma once
#include <string>

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

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	virtual void IncrementRot(float offset);

	void addParent(AGameObject* reference);

	string RetrieveName();
	string RetrieveObjName();
	void setEnabled(bool flag);
	bool IsEnabled();

	Matrix4x4 getLocalMatrix();
	
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

};


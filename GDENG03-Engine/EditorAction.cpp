#include "EditorAction.h"

EditorAction::EditorAction(AGameObject* gameObject)
{
	//capture object state
	this->objectName = gameObject->RetrieveObjName();
	this->localPosition = gameObject->getLocalPosition();
	this->orientation = {};
	Vector3D rotation = gameObject->getLocalRotation();
	this->orientation.x = rotation.m_x;
	this->orientation.y = rotation.m_y;
	this->orientation.z = rotation.m_z;
	this->localScale = gameObject->getLocalScale();
	this->localMatrix = gameObject->getLocalMatrix();
	owner = gameObject;
}



EditorAction::~EditorAction()
{

}

AGameObject* EditorAction::getOwner()
{
	return this->owner;
}

std::string EditorAction::getOwnerName()
{
	return this->objectName;
}

Vector3D EditorAction::getStorePos()
{
	return this->localPosition;
}

Vector3D EditorAction::getStoredScale()
{
	return this->localScale;
}

AGameObject::AQuaternion EditorAction::getStoredOrientation()
{
	return this->orientation;
}

Matrix4x4 EditorAction::getStoredMatrix()
{
	return this->localMatrix;
}
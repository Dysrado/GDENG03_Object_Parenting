#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
	this->parent = nullptr;
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

Vector3D AGameObject::getParentLocalPosition()
{
	if( parent != nullptr)
	{

		Vector3D parentTranslation = parent->getParentLocalPosition();

		return Vector3D(parentTranslation.m_x + localPosition.m_x,
			parentTranslation.m_y + localPosition.m_y,
			parentTranslation.m_z + localPosition.m_z
		);
	}

	return getLocalPosition();
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return localScale;
}

Vector3D AGameObject::getParentLocalScale()
{
	if (parent != nullptr)
	{

		Vector3D parentLocalScale = parent->getParentLocalScale();

		return Vector3D((parentLocalScale.m_x - 1.0f) + localScale.m_x,
			(parentLocalScale.m_y - 1.0f) + localScale.m_y,
			(parentLocalScale.m_z - 1.0f) + localScale.m_z);

		/*return Vector3D((parentLocalScale.m_x) * localScale.m_x,
			(parentLocalScale.m_y ) * localScale.m_y,
			(parentLocalScale.m_z ) * localScale.m_z
		);*/
	}

	return getLocalScale();
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

Vector3D AGameObject::getParentLocalRotation()
{
	if (parent != nullptr)
	{

		Vector3D parentLocalRotation = parent->getLocalRotation();

		return Vector3D(parentLocalRotation.m_x + localRotation.m_x,
			parentLocalRotation.m_y + localRotation.m_y,
			parentLocalRotation.m_z + localRotation.m_z
		);
	}

	return getLocalRotation();
}

void AGameObject::IncrementRot(float offset)
{
}

void AGameObject::SetParent(AGameObject* reference)
{
	this->parent = reference;
	std::cout << "Added Parent " << name << " to " << this->parent->name << std::endl;
}

void AGameObject::RemoveParent(AGameObject* reference)
{
	//Adjust the Parent Transformation:
	//1) Translation
	//2) Scale
	//3) Rotation

	Vector3D parentLocalPosition = parent->getParentLocalPosition();
	Vector3D parentLocalScale = parent->getParentLocalScale();
	Vector3D parentLocalRotation = parent->getParentLocalRotation();

	//Translation
	this->localPosition = Vector3D(
		parentLocalPosition.m_x + localPosition.m_x,
		parentLocalPosition.m_y + localPosition.m_y,
		parentLocalPosition.m_z + localPosition.m_z
	);

	//Scale
	this->localScale = Vector3D(
		(parentLocalScale.m_x - 1.0f) + localScale.m_x,
		(parentLocalScale.m_y - 1.0f) + localScale.m_y,
		(parentLocalScale.m_z - 1.0f) + localScale.m_z
	);

	/*this->localScale = Vector3D(
		(parentLocalScale.m_x) * localScale.m_x,
		(parentLocalScale.m_y) * localScale.m_y,
		(parentLocalScale.m_z) * localScale.m_z
	);*/

	//Rotation
	this->localRotation = Vector3D(
		parentLocalRotation.m_x + localRotation.m_x,
		parentLocalRotation.m_y + localRotation.m_y,
		parentLocalRotation.m_z + localRotation.m_z
	);

	this->localMatrix *= parent->getLocalMatrix() ;
	/*this->localPosition = Vector3D(localMatrix.m_mat[3][0]+localPosition.m_x, 
		localMatrix.m_mat[3][1] + localPosition.m_y,
		localMatrix.m_mat[3][2] + localPosition.m_z);*/

	/*this->localPosition = Vector3D(localMatrix.m_mat[3][0],
		localMatrix.m_mat[3][1],
		localMatrix.m_mat[3][2]);


	this->localScale = Vector3D(localMatrix.m_mat[0][0] + localScale.m_x,
		localMatrix.m_mat[1][1]+ localScale.m_y,
		localMatrix.m_mat[2][2]+ localScale.m_z);*/

	this->parent->RemoveChild(reference);
	this->parent = nullptr;
}

void AGameObject::AttachChild(AGameObject* reference)
{
	childrenList.push_back(reference);
	reference->SetParent(this);
	
}

void AGameObject::RemoveChild(AGameObject* reference)
{

	for(int i = 0; i < childrenList.size();  i++)
	{
		if (childrenList[i] == reference)
		{
			childrenList.erase(childrenList.begin() + i);
			break;
		}
	}

}

bool AGameObject::HasParent()
{
	if (parent == nullptr)
		return false;

	return true;
}

std::vector<AGameObject*> AGameObject::RetrieveAllChildren()
{
	return childrenList;
}


string AGameObject::RetrieveName()
{
	return this->typeName;
}

string AGameObject::RetrieveObjName()
{
	return this->name;
}

string AGameObject::RetrieveParentName()
{
	if (parent == nullptr) {
		return "NULL";
	}

	return parent->RetrieveObjName();
}

void AGameObject::setEnabled(bool flag)
{
	isEnabled = flag;
}

bool AGameObject::IsEnabled()
{
	return this->isEnabled;
}

Matrix4x4 AGameObject::getLocalMatrix()
{
	if(parent == nullptr)
	{
		return localMatrix;
	}
	
	return localMatrix.multiplyTo(parent->getLocalMatrix());
		
}

#include "AGameObject.h"

#include "MathUtils.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localPosition = Vector3D::zeros();
	this->localRotation = Vector3D::zeros();
	this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
	this->localMatrix.setIdentity();
	this->parent = nullptr;
}

AGameObject::~AGameObject()
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
	this->overrideMatrix = false;
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
	this->overrideMatrix = false;
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
	this->overrideMatrix = false;
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

		return Vector3D((parentLocalScale.m_x ) * localScale.m_x,
			(parentLocalScale.m_y ) * localScale.m_y,
			(parentLocalScale.m_z ) * localScale.m_z);
	}

	return getLocalScale();
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
	this->overrideMatrix = false;
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
	//Case 1 : Setting a parent but has no previous parent and All are rest
	//Solution = is to leave at is

	//case 2: Setting a parent but has no previous parent and still retain their previous transformation
	//Expected: Need to readjust first then set the new  position and scaling

	//case 3: Setting a parent but it has the previous parent transform and their own previous transformation.
	//Expected: Similar to case 2

	Matrix4x4 temp;


	//Case 1 & 2
	if (!this->HasParent())
	{
		Matrix4x4 ownMatrix = this->computeLocalMatrix();
		Matrix4x4 ownWorldMatrix = this->computeWorldMatrix();
		parent = reference;
		Matrix4x4 FinalMatrix = parent->computeWorldMatrix();

		//Case 1
		temp.setIdentity();

		if(ownMatrix == temp) //Identity Check
		{
			cout << "Case 1:" << endl; return;
		}
		
		//Case 2
		//Readjusting Parent Transform
		Vector3D parentScale = parent->getParentLocalScale();

		parentScale = Vector3D(
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[0][0], FinalMatrix.m_mat[0][1], FinalMatrix.m_mat[0][2]),
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[1][0], FinalMatrix.m_mat[1][1], FinalMatrix.m_mat[1][2]),
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[2][0], FinalMatrix.m_mat[2][1], FinalMatrix.m_mat[2][2])
		);

		temp.setIdentity();
		temp.setScale(localScale);

		this->localScale = Vector3D(
			localScale.m_x / parentScale.m_x,
			localScale.m_y / parentScale.m_y,
			localScale.m_z / parentScale.m_z
		);

		

		
		
		cout << "Child No Parent" << endl;
		
		ownWorldMatrix.debugPrint();

		cout << "Parent" << endl;
		
		FinalMatrix.debugPrint();
		

		this->localPosition = Vector3D(
			 ownWorldMatrix.m_mat[3][0] - FinalMatrix.m_mat[3][0],
			 ownWorldMatrix.m_mat[3][1] - FinalMatrix.m_mat[3][1],
			 ownWorldMatrix.m_mat[3][2] - FinalMatrix.m_mat[3][2]
		);

		
		


		cout << "Case 2:" << endl;
		return;
	}

	//Case 3

	//Step 1: Get Previous Parent Transform
	Matrix4x4 prevParentMatrix = parent->computeWorldMatrix();

	//Step 2: Remove Child and Get its Own Matrix
	parent->RemoveChild(this);
	this->RemoveParent(parent);
	Matrix4x4 ownWorldMatrix = this->computeWorldMatrix();

	//Step 3: Get The attaching parent world Matrix 
	this->parent = reference;
	Matrix4x4 FinalMatrix = parent->computeWorldMatrix();
	
	
	
	//Scale Transformation
	Vector3D parentScale = parent->getParentLocalScale();

	parentScale = Vector3D(
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[0][0], FinalMatrix.m_mat[0][1], FinalMatrix.m_mat[0][2]),
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[1][0], FinalMatrix.m_mat[1][1], FinalMatrix.m_mat[1][2]),
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[2][0], FinalMatrix.m_mat[2][1], FinalMatrix.m_mat[2][2])
	);

	temp.setIdentity();
	temp.setScale(localScale);

	this->localScale = Vector3D(
		localScale.m_x / parentScale.m_x,
		localScale.m_y / parentScale.m_y,
		localScale.m_z / parentScale.m_z
	);


	// Position Scale
	this->localPosition = Vector3D(
		ownWorldMatrix.m_mat[3][0] - FinalMatrix.m_mat[3][0],
		ownWorldMatrix.m_mat[3][1] - FinalMatrix.m_mat[3][1],
		ownWorldMatrix.m_mat[3][2] - FinalMatrix.m_mat[3][2]
	);
	
	std::cout << "Added Parent " << name << " to " << this->parent->name << std::endl;
}

void AGameObject::RemoveParent(AGameObject* reference)
{
	//Adjust the Parent Transformation:
	//1) Translation
	//2) Scale
	//3) Rotation

	Matrix4x4 FinalMatrix = computeWorldMatrix();

	//Translation
	this->localPosition = Vector3D(FinalMatrix.m_mat[3][0], FinalMatrix.m_mat[3][1], FinalMatrix.m_mat[3][2]);
	

	//Scale
	this->localScale = this->getParentLocalScale();


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

bool AGameObject::containSameParent(AGameObject* reference)
{
	if(parent != nullptr)
	{
		//check if the same or check its root parent
		bool same = parent->containSameParent(reference) || reference == parent;

		if (same)
			return same;
		else
			return false;
	}

	return false;
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
	return localMatrix;
	/*if(parent == nullptr)
	{
		
	}
	
	return localMatrix.multiplyTo(parent->getLocalMatrix());*/
		
}

Matrix4x4 AGameObject::getParentLocalMatrix()
{
	if (parent == nullptr)
	{
		return computeLocalMatrix();
	}

	
	return computeLocalMatrix().multiplyTo(parent->getParentLocalMatrix());
}

// This function is meant for retrieving the finalMatrixTransformation including self
Matrix4x4 AGameObject::computeLocalMatrix()
{
	Matrix4x4 finalMatrix;
	Matrix4x4 temp;


	finalMatrix.setIdentity();
	temp.setIdentity();

	//Scaling
	temp.setScale(this->getLocalScale());
	finalMatrix *= temp;


	//Initial Rotation
	Matrix4x4 Rot;
	Rot.setIdentity();

	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().m_x);
	Rot *= temp;

	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().m_y);
	Rot *= temp;

	temp.setIdentity();
	temp.setRotationZ(this->getLocalRotation().m_z);

	Rot *= temp;
	finalMatrix *= Rot;

	//Translation
	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	finalMatrix *= temp;

	return finalMatrix;
}

Matrix4x4 AGameObject::computeWorldMatrix()
{
	Matrix4x4 finalMatrix;
	Matrix4x4 temp;


	finalMatrix.setIdentity();
	temp.setIdentity();

	//Scaling
	temp.setScale(this->getLocalScale());
	finalMatrix *= temp;


	//Initial Rotation
	Matrix4x4 Rot;
	Rot.setIdentity();

	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().m_x);
	Rot *= temp;

	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().m_y);
	Rot *= temp;

	temp.setIdentity();
	temp.setRotationZ(this->getLocalRotation().m_z);

	Rot *= temp;
	finalMatrix *= Rot;

	//Translation
	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	finalMatrix *= temp;

	// If Parent Exists, then Follow Parent Transform
	if (parent != nullptr)
	{
		finalMatrix *= parent->getParentLocalMatrix(); //Fundamental problem
	}

	return finalMatrix;
}

void AGameObject::updateLocalMatrix()
{
	//setup transformation matrix for drawing.
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);


	//Addition of Object Parenting
	if(this->HasParent())
	{
		allMatrix = allMatrix.multiplyTo(parent->getParentLocalMatrix());
	}
	this->localMatrix = allMatrix;
}



void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentByName(string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}



AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

AGameObject::ComponentList AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setIdentity(); newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setIdentity(); transMatrix.setTranslation(this->localPosition);

	this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	this->overrideMatrix = true;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setIdentity(); scaleMatrix.setScale(Vector3D(1, 1, 1)); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getLocalRotation();


	Matrix4x4 xMatrix; xMatrix.setIdentity(); xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setIdentity(); yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setIdentity(); zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	//float* oneDMatrix = MathUtils::convertInto1D(allMatrix);

	return allMatrix.getFloatArray();// allMatrix.getMatrix();
}

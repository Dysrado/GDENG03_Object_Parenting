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

	/*if (object.parent) {
		glm::mat4 parentWorldTransform = object.parent->localTransform * UpdateWorldTransform(*object.parent);
		object.localTransform = glm::translate(glm::mat4(1.0), object.translation);
		return parentWorldTransform * object.localTransform;
	}
	else {
		object.localTransform = glm::translate(glm::mat4(1.0), object.translation);
		return object.localTransform;
	}*/
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

		return Vector3D((parentLocalScale.m_x ) * localScale.m_x,
			(parentLocalScale.m_y ) * localScale.m_y,
			(parentLocalScale.m_z ) * localScale.m_z);
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

		

		
		//Matrix4x4 FinalMatrix = parent->computeWorldMatrix();
		//Option 1:

		//this->localPosition = Vector3D(
		//	localPosition.m_x - FinalMatrix.m_mat[3][0],
		//	localPosition.m_y - FinalMatrix.m_mat[3][1],
		//	localPosition.m_z - FinalMatrix.m_mat[3][2]
		//);

		//Option 1:
		cout << "Child No Parent" << endl;
		
		ownWorldMatrix.debugPrint();

		cout << "Parent" << endl;
		
		FinalMatrix.debugPrint();
		

		this->localPosition = Vector3D(
			 ownWorldMatrix.m_mat[3][0] - FinalMatrix.m_mat[3][0],
			 ownWorldMatrix.m_mat[3][1] - FinalMatrix.m_mat[3][1],
			 ownWorldMatrix.m_mat[3][2] - FinalMatrix.m_mat[3][2]
		);

		//std::cout << "A World Position %s, % "



		////Option 2:
		//Vector3D parentPosition = parent->getParentLocalPosition();
		//this->localPosition = Vector3D(
		//	localPosition.m_x + parentPosition.m_x,
		//	localPosition.m_y + parentPosition.m_y,
		//	localPosition.m_z + parentPosition.m_z
		//	);



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

	/*this->localScale = Vector3D(
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[0][0], FinalMatrix.m_mat[0][1], FinalMatrix.m_mat[0][2]),
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[1][0], FinalMatrix.m_mat[1][1], FinalMatrix.m_mat[1][2]),
		MathUtils::extractScaleTransform(FinalMatrix.m_mat[2][0], FinalMatrix.m_mat[2][1], FinalMatrix.m_mat[2][2])
	);*/

	//Rotation
	/*this->localRotation = Vector3D(
		parentLocalRotation.m_x + localRotation.m_x,
		parentLocalRotation.m_y + localRotation.m_y,
		parentLocalRotation.m_z + localRotation.m_z
	);*/

	//Compuation Experiment For Rotation

	//Matrix4x4 posMat;
	//posMat.setTranslation(localPosition);
	//posMat.inverse();

	//Matrix4x4 scaleMat;
	//scaleMat.setScale(localScale);
	//scaleMat.inverse();

	//Matrix4x4 rotMat = posMat.multiplyTo(FinalMatrix.multiplyTo(scaleMat));

	////Matrix4x4 rotMat = scaleMat.multiplyTo(FinalMatrix.multiplyTo(posMat));

	///*this->localRotation = Vector3D(
	//	rotMat.m_mat[0][3], rotMat.m_mat[1][3], rotMat.m_mat[2][3]
	//);*/

	//this->localRotation = Vector3D(
	//	rotMat.m_mat[3][0], rotMat.m_mat[3][1], rotMat.m_mat[3][2]
	//);

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
	if(parent == nullptr)
	{
		return localMatrix;
	}
	
	return localMatrix.multiplyTo(parent->getLocalMatrix());
		
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
		finalMatrix *= parent->getLocalMatrix(); //Fundamental problem
	}

	return finalMatrix;
}

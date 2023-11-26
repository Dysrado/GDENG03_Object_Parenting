#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner, BodyType type) : AComponent(name, AComponent::ComponentType::Physics, owner)
{

	//whenever a new physics component is initialized. Register to physics system
	PhysicsSystem* physicsSystem = BaseComponentSystem::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	Transform transform;
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape;
	//Resolving Issues With Rigid Body Type

	boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2.0f,
		scale.m_y / 2.0f, scale.m_z / 2.0f)); //half extentP

	


	this->rigidBody = physicsWorld->createRigidBody(transform);
	//this->rigidBody->setLocalCenterOfMass(Vector3(owner->getLocalPosition().m_x, owner->getLocalPosition().m_y, owner->getLocalPosition().m_z));
	collider = this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	
	

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);

	//Collision Filtering 
	if (type == BodyType::DYNAMIC) 
	{
		collider->setCollisionCategoryBits(CATEGORY1);
		collider->setCollideWithMaskBits(CATEGORY2 | CATEGORY3);
		this->rigidBody->setType(BodyType::DYNAMIC);
	}

	else
	{
		collider->setCollisionCategoryBits(CATEGORY2);
		collider->setCollideWithMaskBits(CATEGORY1 | CATEGORY3);
		rigidBody->setType(BodyType::STATIC);
	}

	forceVector = new Vector3(0, 0, 0);
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);

	//getOwner()->setRotation(transform.getOrientation().x, transform.getOrientation().y, transform.getOrientation().z);
	//getOwner()->setPosition(transform.getPosition().x, transform.getPosition().y, transform.getPosition().z);

	

	timer += deltaTime;
	if(timer > 2.0f)
	{
		if(rigidBody->getType() == BodyType::DYNAMIC && !isSelfCollision )
		{
			collider->setCollisionCategoryBits(CATEGORY3);
			collider->setCollideWithMaskBits( CATEGORY1 | CATEGORY2 | CATEGORY3);
			isSelfCollision = true;
			std::cout << "My component is UPDATED: " << this->name << "\n";
		}
			
	}
	
	//std::cout << "My component is updating: " << this->name << "\n";
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}
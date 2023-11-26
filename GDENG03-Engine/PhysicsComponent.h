#pragma once
#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;
class PhysicsComponent : public AComponent
{
public:
	enum CollisionFilter
	{
		CATEGORY1 = 0x0001,
		CATEGORY2 = 0x0002,
		CATEGORY3 = 0x0004
	};

	PhysicsComponent(String name, AGameObject* owner, BodyType type);
	~PhysicsComponent();
	void perform(float deltaTime) override;
	RigidBody* getRigidBody();

private:
	float mass = 10.0f; //in kilograms
	float timer = 0;
	bool isSelfCollision = false;
	RigidBody* rigidBody;
	Collider* collider;
};

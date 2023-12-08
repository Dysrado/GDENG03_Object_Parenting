#include "ScenePlayOptions.h"
#include "GameObjectManager.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include "EngineBackend.h"
#include "AGameObject.h"

ScenePlayOptions::ScenePlayOptions() : AUIScreen("ScenePlayOptions")
{
}

ScenePlayOptions::~ScenePlayOptions()
{
}

void ScenePlayOptions::drawUI()
{
	EngineBackend* backend = EngineBackend::getInstance();

	ImGui::Begin("Scene Play Options", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 75));
	ImGui::SameLine();

	//TODO: Use memento pattern for saving state of objects
	if (backend->getMode() == EngineBackend::EDITOR) {
		if (ImGui::Button("Play")) 
		{ 
			EngineBackend::getInstance()->setMode(EngineBackend::PLAY); 

			PhysicsSystem::ComponentList components = BaseComponentSystem::getInstance()->getPhysicsSystem()->getAllComponents();
			for (int i = 0; i < components.size(); i++) {
				if (components[i]->getRigidBody()->getType() != BodyType::STATIC) 
				{
					//Define Owner
					AGameObject* aObject = components[i]->getOwner();

					components[i]->getOwner()->detachComponent(components[i]);
					float mass = components[i]->getRigidBody()->getMass();
					bool isGravityEnabled = components[i]->getRigidBody()->isGravityEnabled();
					BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(components[i]);

					aObject->attachComponent(new PhysicsComponent("Physics_Component" + components[i]->getOwner()->RetrieveObjName(),
						aObject, BodyType::DYNAMIC));
					PhysicsComponent* newPObject = (PhysicsComponent*)aObject->findComponentByName("Physics_Component" + aObject->RetrieveObjName());
					newPObject->getRigidBody()->setMass(mass);
					newPObject->getRigidBody()->enableGravity(isGravityEnabled);
					delete components[i];
					
					


					// Delete Components causes some issues not sure why, but without the delete there becomes a memory leak and the engine lags
					//delete components[i];

				}
				
			}
		}
	}

	else if (backend->getMode() != EngineBackend::EDITOR) {
		if (ImGui::Button("Stop")) { EngineBackend::getInstance()->setMode(EngineBackend::EDITOR); }
	}

	ImGui::SameLine();

	if (backend->getMode() == EngineBackend::PLAY) {
		if (ImGui::Button("Pause")) { EngineBackend::getInstance()->setMode(EngineBackend::PAUSED); }
	}
	else if (backend->getMode() == EngineBackend::PAUSED) {
		if (ImGui::Button("Resume")) { EngineBackend::getInstance()->setMode(EngineBackend::PLAY); }
	}

	ImGui::SameLine();
	if (backend->getMode() == EngineBackend::PAUSED && ImGui::Button("Frame Step")) { EngineBackend::getInstance()->startFrameStep(); }
	ImGui::End();
}

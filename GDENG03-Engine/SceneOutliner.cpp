#include "SceneOutliner.h"

#include "GameObjectManager.h"
#include "UIManager.h"

static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding |
ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;


SceneOutliner::SceneOutliner(const String name) : AUIScreen(name)
{
}

SceneOutliner::~SceneOutliner()
{
}

void SceneOutliner::drawUI()
{
	float xLength = UIManager::WINDOW_WIDTH * 0.2f;
	float yLength = UIManager::WINDOW_HEIGHT * (1.0f - 0.025f);

	float xPos = UIManager::WINDOW_WIDTH - ((UIManager::WINDOW_WIDTH * 0.21f * 2.0f));
	float yPos = UIManager::WINDOW_HEIGHT * 0.025f;

	float xButtonSize = UIManager::WINDOW_WIDTH * 0.19f;
	float yButtonSize = UIManager::WINDOW_HEIGHT * 0.025f;

	ImGui::Begin("SceneOutliner", NULL, ImGuiWindowFlags_NoResize | 
		ImGuiWindowFlags_NoMove );


	//Window Specificatioon
	ImGui::SetWindowSize( ImVec2(xLength, yLength));
	ImGui::SetWindowPos(ImVec2(xPos, yPos));
	int id = 0, i = 1;
	



	//TODO for Engine Replication: Check button -> clickable text w/ drop down

	//Display: Through Tree
	std::vector<AGameObject*> aParentList = GameObjectManager::getInstance()->retrieveBaseParentObject();
	for (AGameObject* aObject : aParentList)
	{
		
		id++;
		String name = aObject->RetrieveObjName();      // trying RetrieveObjName over RetriveName
		name.append("##"); name.append(to_string(id)); //id for gameobject

		ImGuiTreeNodeFlags node_flags = base_flags;

		if (GameObjectManager::getInstance()->isSelectedOnObjectList(aObject))
			node_flags |= ImGuiTreeNodeFlags_Selected;
		
		bool treeNodeOpen = ImGui::TreeNodeEx(name.c_str(), node_flags, aObject->RetrieveObjName().c_str(), i);

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		{
			if (GameObjectManager::getInstance()->IsLinkingEnabled())
			{
				AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

				//Checking Edge Case for attaching on its own child
				if(!aObject->containSameParent(selectedObject))
				{
					aObject->AttachChild(selectedObject);
				}

				GameObjectManager::getInstance()->SetLinkingEnabled(false);
			}

			//Multi-Selecting
			if (ImGui::GetIO().KeyCtrl)
				GameObjectManager::getInstance()->setSelectedObject(aObject, true);
			else
				GameObjectManager::getInstance()->setSelectedObject(aObject, false);
			
		}
			

		if (treeNodeOpen)
		{
			//Draw all children nodes
			DrawtreeNode(&id, aObject);
			ImGui::TreePop();
		}
		i++;
	}

	
	ImGui::End();
}

void SceneOutliner::DrawtreeNode(int *id, AGameObject* aObject)
{

	int node_clicked = -1, i = 1;
	std::vector<AGameObject*> aChildList = aObject->RetrieveAllChildren();
	for (AGameObject* aObject : aChildList)
	{
		id++;
		i++;

		String name = aObject->RetrieveObjName();      // trying RetrieveObjName over RetriveName
		name.append("##"); name.append(to_string(*id)); //id for gameobject

		ImGuiTreeNodeFlags node_flags = base_flags;
		
		if (GameObjectManager::getInstance()->isSelectedOnObjectList(aObject))
			node_flags |= ImGuiTreeNodeFlags_Selected;

		bool treeNodeOpen = ImGui::TreeNodeEx(name.c_str(), node_flags, 
			aObject->RetrieveObjName().c_str(), i);


		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
		{
			if(GameObjectManager::getInstance()->IsLinkingEnabled())
			{
				AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();

				//Checking Edge Case for attaching on its own child
				if (!aObject->containSameParent(selectedObject))
				{
					aObject->AttachChild(selectedObject);
					
				}
				GameObjectManager::getInstance()->SetLinkingEnabled(false);
			}

			//Multi-Selecting
			if (ImGui::GetIO().KeyCtrl)
				GameObjectManager::getInstance()->setSelectedObject(aObject, true);
			else
				GameObjectManager::getInstance()->setSelectedObject(aObject, false);
			
		}


		if (treeNodeOpen)
		{
			DrawtreeNode(id, aObject);
			ImGui::TreePop();
		}


	}

	

}

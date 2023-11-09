#include "SceneOutliner.h"

#include "GameObjectManager.h"
#include "UIManager.h"

static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding |
ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
static int selection_mask = (1 << 2);

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
	int node_clicked = -1;

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
				////Case 1: If a children still has attachment to its parent
				//if (GameObjectManager::getInstance()->getSelectedObject()->HasParent())
				//	GameObjectManager::getInstance()->getSelectedObject()->
				//	RemoveParent(GameObjectManager::getInstance()->getSelectedObject());

				
				//Case 2: if a children has no attachment to its parent
				aObject->AttachChild(GameObjectManager::getInstance()->getSelectedObject());
				GameObjectManager::getInstance()->SetLinkingEnabled(false);
			}

			//Multi-Selecting
			if (ImGui::GetIO().KeyCtrl)
				GameObjectManager::getInstance()->setSelectedObject(aObject, true);
			else
				GameObjectManager::getInstance()->setSelectedObject(aObject, false);
			node_clicked = i;
		}
			

		if (treeNodeOpen)
		{
			DrawtreeNode(&id, aObject);
			ImGui::TreePop();
		}
		i++;
	}

	//if (node_clicked != -1)
	//{
	//	// Update selection state
	//	// (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
	//	if (ImGui::GetIO().KeyCtrl)
	//		selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
	//	else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
	//		selection_mask = (1 << node_clicked);           // Click to single-select
	//}



	////Display:through Button
	//std::vector<AGameObject* >list = GameObjectManager::getInstance()->getAllObjects();
	//for(AGameObject* aObject : list)
	//{
	//	id++;
	//	String name = aObject->RetrieveObjName(); // trying RetrieveObjName over RetriveName
	//	name.append("##"); name.append(to_string(id)); //id for gameobject
	//	if(ImGui::Button(name.c_str(), ImVec2(xButtonSize, yButtonSize)))
	//	{
	//		GameObjectManager::getInstance()->setSelectedObject(aObject);
	//	}

	//}
	
	
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
				////Case 3: If a children still has attachment to its parent
				//if (GameObjectManager::getInstance()->getSelectedObject()->HasParent())
				//	GameObjectManager::getInstance()->getSelectedObject()->
				//		RemoveParent(GameObjectManager::getInstance()->getSelectedObject());

				//Case 2: if a children has no attachment to its parent
				aObject->AttachChild(GameObjectManager::getInstance()->getSelectedObject());
				GameObjectManager::getInstance()->SetLinkingEnabled(false);
			}
			//Multi-Selecting
			if (ImGui::GetIO().KeyCtrl)
				GameObjectManager::getInstance()->setSelectedObject(aObject, true);
			else
				GameObjectManager::getInstance()->setSelectedObject(aObject, false);
			node_clicked = i;
		}

		if (treeNodeOpen)
		{
			DrawtreeNode(id, aObject);
			ImGui::TreePop();
		}


	}

	if (node_clicked != -1)
	{
		// Update selection state
		// (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
		if (ImGui::GetIO().KeyCtrl)
			selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
		else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
			selection_mask = (1 << node_clicked);           // Click to single-select
	}

}

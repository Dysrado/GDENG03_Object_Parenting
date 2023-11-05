#pragma once
#include "AGameObject.h"
#include "UINames.h"

class SceneOutliner : public AUIScreen
{
public:
	SceneOutliner(const String name);
	~SceneOutliner();

	void drawUI() override;

private:
	void DrawtreeNode(int *id, AGameObject* aObject);
};


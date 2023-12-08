#pragma once
#include "AUIScreen.h"
class EditorAction;

class ActionMemento
{
public:
	ActionMemento(EditorAction* oldAction, EditorAction* newAction);
	~ActionMemento();

	EditorAction* getOldAction();
	EditorAction* getNewAction();

	std::string getOwnerName();

private:
	EditorAction* oldAction;
	EditorAction* newAction;
};


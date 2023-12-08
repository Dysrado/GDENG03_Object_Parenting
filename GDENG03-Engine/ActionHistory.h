#pragma once
#include <stack> 

class ActionMemento;
class EditorAction;
class AGameObject;

class ActionHistory
{
public:
	// Change into Memento
	typedef std::stack<ActionMemento*> ActionStack;
	static ActionHistory* getInstance();
	static void initialize();
	static void destroy();

	void startRecordAction(AGameObject* gameObject);
	void endRecordAction(AGameObject* gameObject);

	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	EditorAction* undoAction();
	EditorAction* redoAction();
	void clear();

private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};
	ActionHistory& operator=(ActionHistory const&) {};
	
	static ActionHistory* sharedInstance;

	AGameObject* currentGameObject;
	EditorAction* oldEditorAction;

	ActionStack actionsPerformed;
	ActionStack actionsUndid;

};


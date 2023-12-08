#include "ActionHistory.h"
#include "EngineBackend.h"
#include "ActionMemento.h"
#include "EditorAction.h"
#include "ActionHistory.h"

ActionHistory* ActionHistory::sharedInstance = nullptr;
ActionHistory* ActionHistory::getInstance()
{
    return sharedInstance;
}

void ActionHistory::initialize()
{
    sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
    delete sharedInstance;
}

void ActionHistory::startRecordAction(AGameObject* gameObject)
{
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR) {
		oldEditorAction = new EditorAction(gameObject);
	}
}

void ActionHistory::endRecordAction(AGameObject* gameObject)
{
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR) {
		ActionMemento* editorAction = new ActionMemento(oldEditorAction, new EditorAction(gameObject));
		this->actionsPerformed.push(editorAction);
	}
}

bool ActionHistory::hasRemainingUndoActions()
{
	return !this->actionsPerformed.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
	return !this->actionsUndid.empty();
}

EditorAction* ActionHistory::undoAction()
{
	if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR) {
		return NULL;
	}

	if (this->hasRemainingUndoActions()) {
		ActionMemento* action = this->actionsPerformed.top();
		this->actionsUndid.push(action);
		this->actionsPerformed.pop();
		return action->getOldAction();
	}
	else {
		return NULL;
	}
}

EditorAction* ActionHistory::redoAction()
{
	if (EngineBackend::getInstance()->getMode() != EngineBackend::EditorMode::EDITOR) {
		return NULL;
	}

	if (this->hasRemainingRedoActions()) {
		ActionMemento* action = actionsUndid.top();
		this->actionsUndid.pop();
		this->actionsPerformed.push(action);
		return action->getNewAction();
	}
	else {
		return NULL;
	}
}

void ActionHistory::clear()
{
	while (this->hasRemainingUndoActions()) {
		ActionMemento* action = this->actionsPerformed.top();
		delete action;
		this->actionsPerformed.pop();
	}

	while (this->hasRemainingRedoActions()) {
		ActionMemento* action = this->actionsUndid.top();
		delete action;
		this->actionsUndid.pop();
	}
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}

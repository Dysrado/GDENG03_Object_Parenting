#pragma once
#include <string>

class  UIManager;

class AUIScreen
{
protected:
	typedef std::string String;

	AUIScreen(String name);
	~AUIScreen();

	void setEnabled(bool flag);

	String getName();
	virtual void drawUI();

	bool getEnabled();


	String name;
	bool isEnabled;


	friend class UIManager;
};


#pragma once
#define NOMINMAX
#include <Windows.h>


class EngineTime;

class Window
{
public:
	Window();
	//Initialize the window
	bool init();
	bool broadcast();
	//Release the window
	bool release();
	bool isRun();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);


	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	

	virtual ~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;

private:
	friend class EngineTime;
	
	
};
#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	//Initialize the window
	bool init();
	
	//Release the window
	bool release();

	bool isRun();
	bool broadcast();

	//Events
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	~Window();
protected:
	//The unique instance number of the program window
	HWND hwnd;
	bool is_run;
};


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
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy() = 0;
	virtual void onFocus();
	virtual void onLoseFocus();

	//Sizes
	RECT getClientWindowRect();

	void setHWND(HWND hwnd);

	~Window();
protected:
	//The unique instance number of the program window
	HWND hwnd;
	bool is_run;
};


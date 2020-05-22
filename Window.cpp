#include "Window.h"
#include <stdexcept>


Window::Window()
{

}

// Message processing for a window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		//Event fired when the window will be created
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		//Event fired when the window will be destroyed
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc; // Info about window class
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX); // Size of struct
	wc.cbWndExtra = NULL; //The amount of allocated memory when creating
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Window coloring
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Standart cursor

	//Standart icon
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	wc.hInstance = NULL; //App descriptor
	wc.lpszClassName = L"MyWindowClass"; 
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	
	if (!::RegisterClassEx(&wc))
	{
		// Register window class for subsequent use when calling CreateWindow or CreateWindowEx
		return false;
	}



	hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Appllication", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	if (!hwnd)
	{
		return false;
	}

	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);

	
	//Set flat to true to indicate that the window is init and running
	is_run = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	//Message in the application message processing queue
	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	this->onUpdate();

	Sleep(1);

	return true;
}

bool Window::release()
{
	//Destroy the window
	if (!::DestroyWindow(hwnd))
	{
		return false;
	}
	return true;
}

bool Window::isRun()
{
	return is_run;
}

void Window::onCreate()
{
}

void Window::onUpdate()
{
}

void Window::onDestroy()
{
	is_run = false;
}

Window::~Window()
{
}

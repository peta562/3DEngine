#include "AppWindow.h"



void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	GraphicsEngine::get()->createSwapChain();
	swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();

	swap_chain->init(this->hwnd, rc.right - rc.left, rc.bottom - rc.top);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	swap_chain->release();
	GraphicsEngine::get()->release();
}

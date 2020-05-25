#pragma once
#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool init(HWND hwnd, UINT width, UINT height);
	bool release();
private:
	IDXGISwapChain* swap_chain; // one or more surfaces for swap buffers
};


#pragma once
#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool init(HWND hwnd, UINT width, UINT height);
	bool release();
	bool present(bool vsync);
private:
	IDXGISwapChain* swap_chain; // one or more surfaces for swap buffers
	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;

	friend class DeviceContext;
};


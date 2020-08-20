#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{

}

SwapChain::~SwapChain()
{

}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	ID3D11Device* device =  GraphicsEngine::get()->d3d_device;
	DXGI_SWAP_CHAIN_DESC dsc;

	ZeroMemory(&dsc, sizeof(dsc)); // Fills a block of memory with 0.
	dsc.BufferCount = 1;
	dsc.BufferDesc.Width = width;
	dsc.BufferDesc.Height = height;
	dsc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dsc.BufferDesc.RefreshRate.Numerator = 60;
	dsc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dsc.OutputWindow = hwnd;
	dsc.SampleDesc.Count = 1;
	dsc.SampleDesc.Quality = 0;
	dsc.Windowed = TRUE;

	//Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = GraphicsEngine::get()->dxgi_factory->CreateSwapChain(device, &dsc, &swap_chain);
	
	if (FAILED(hr))
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	hr = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool SwapChain::release()
{
	swap_chain->Release();
	delete this;
	return true;

}

bool SwapChain::present(bool vsync)
{
	swap_chain->Present(vsync, NULL); //sync interval (false - presentation occurs immidiately w/o any sync)
	return true;
}

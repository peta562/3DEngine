#include "GraphicsEngine.h"
#include "SwapChain.h"

GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE  driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		// Device that represent the display adapter
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, 
			num_feature_levels, D3D11_SDK_VERSION, &d3d_device, &feature_level, &imn_context);
		
		if (SUCCEEDED(res))
		{
			break;
			++driver_type_index;
		}

	}
	if (FAILED(res))
	{
		return false;
	}
	
	d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device);
	dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgi_adapter);
	dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgi_factory);
	

	return true;
}

bool GraphicsEngine::release()
{
	dxgi_device->Release();
	dxgi_adapter->Release();
	dxgi_factory->Release();

	imn_context->Release();
	d3d_device->Release();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{

}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

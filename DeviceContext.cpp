#include "DeviceContext.h"
#include "SwapChain.h"


DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):device_context(device_context)
{
}

DeviceContext::~DeviceContext()
{
	
}

bool DeviceContext::release()
{
	device_context->Release();
	delete this;
	return true;
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha }; //vector of 4 channels of the color


	device_context->ClearRenderTargetView(swap_chain->rtv, clear_color);
	return true;
}

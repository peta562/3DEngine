#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

#include <d3dcompiler.h>

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
		}
		++driver_type_index;
		

	}
	if (FAILED(res))
	{
		return false;
	}

	imn_device_context = new DeviceContext(imn_context);
	
	d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device);
	dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgi_adapter);
	dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgi_factory);
	

	return true;
}

bool GraphicsEngine::release()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	dxgi_device->Release();
	dxgi_adapter->Release();
	dxgi_factory->Release();

	imn_device_context->release();
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

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return this->imn_device_context;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

bool GraphicsEngine::createShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	d3d_device->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	d3d_device->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
	return true;
}
bool GraphicsEngine::setShaders()
{
	imn_context->VSSetShader(m_vs, nullptr, 0);
	imn_context->PSSetShader(m_ps, nullptr, 0);
	return true;
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();

}

#pragma once
#include <d3d11.h>


class SwapChain;
class DeviceContext;
class VertexBuffer;

class GraphicsEngine
{
public:
	GraphicsEngine();
	// Init the graphics engine and DirectX 11 device
	bool init();
	// Release all the resources loaded
	bool release();
	bool createShaders();
	bool setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size);

	~GraphicsEngine();


public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();

private:
	ID3D11Device* d3d_device;
	D3D_FEATURE_LEVEL feature_level;
	ID3D11DeviceContext* imn_context;
	
	IDXGIDevice* dxgi_device;
	IDXGIAdapter* dxgi_adapter;
	IDXGIFactory* dxgi_factory;

private:
	DeviceContext* imn_device_context; //Immediate device context for immediate execution of rendering commands

private:
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

private:
	friend class SwapChain;
	friend class VertexBuffer;

public:
	static GraphicsEngine* get();
};


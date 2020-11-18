#pragma once
#include <d3d11.h>


class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class IndexBuffer;

class GraphicsEngine
{
public:
	GraphicsEngine();
	// Init the graphics engine and DirectX 11 device
	bool init();
	// Release all the resources loaded
	bool release();
	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompileShader();

	~GraphicsEngine();


public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	VertexBuffer* createVertexBuffer();
	IndexBuffer* createIndexBuffer();
	ConstantBuffer* createConstantBuffer();
	VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
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
	ID3DBlob* m_blob = nullptr;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class IndexBuffer;

public:
	static GraphicsEngine* get();
};


#pragma once
#include <d3d11.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	// Init the graphics engine and DirectX 11 device
	bool init();
	// Release all the resources loaded
	bool release();
	~GraphicsEngine();
	static GraphicsEngine* get();
private:
	ID3D11Device* d3d_device;
	D3D_FEATURE_LEVEL feature_level;
	ID3D11DeviceContext* imn_context;
};


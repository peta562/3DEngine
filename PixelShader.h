#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	void release();
	~PixelShader();
private:
	bool init(const void* shader_byte_code, size_t byte_code_size);
	ID3D11PixelShader* ps;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};


#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

class AppWindow : public Window
{
public:
	AppWindow() = default;

	// Initialize via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* swap_chain;
	VertexBuffer* vertex_buffer;
	VertexShader* vertex_shader;
	PixelShader* pixel_shader;
	ConstantBuffer* constant_buffer;
};

#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow() = default;
	void updateQuadPosition();

	// Initialize via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onLoseFocus() override;
	
	// Унаследовано через InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;

	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

private:
	SwapChain* swap_chain;
	VertexBuffer* vertex_buffer;
	VertexShader* vertex_shader;
	PixelShader* pixel_shader;
	ConstantBuffer* constant_buffer;
	IndexBuffer* index_buffer;
private:
	float old_delta;
	float new_delta;
	float delta_time;

	float delta_pos;
	float delta_scale;

	float rotation_x = 0;
	float rotation_y = 0;
	
	float scale_cube = 1;
};

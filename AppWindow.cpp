#include "AppWindow.h"
#include <Windows.h>

struct Vector3
{
	float x, y, z;
};

struct Vertex
{
	Vector3 position;
	Vector3 new_position;
	Vector3 color;
	Vector3 new_color;
};

__declspec(align(16)) // because directX stored data in video memory in chanks of 16 bytes
struct Constant
{
	unsigned int time;
};

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();

	swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();

	swap_chain->init(this->hwnd, rc.right - rc.left, rc.bottom - rc.top);
	

	// {x, y, z} from -1 to 1
	Vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f,   -0.25f, -0.11f, 0.0f,   1, 0, 0,   1, 1, 1}, // pos1  new_pos1   color1  new_color1
		{-0.5f, 0.5f, 0.0f,    -0.77f, 0.78f, 0.0f,    0, 1, 1,   0, 0, 1}, // pos2  new_pos2   color2  new_color2
		{0.5f, -0.5f, 0.0f,    0.75f, -0.72f, 0.0f,    0, 0, 1,   1, 0, 0}, // pos3  new_pos3   color3  new_color3
		{0.4f, 0.2f, 0.0f,     0.82f, 0.79f, 0.0f,     1, 1, 1,   0, 0, 1}, // pos4  new_pos4   color4  new_color4
		//{0.0f, -0.5f, 0.0f}, // pos5
		//{-0.5f, -0.5f, 0.0f} // pos6

	};

	vertex_buffer=GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	
	
	vertex_shader = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	vertex_buffer->load(list, sizeof(Vertex), size_list, shader_byte_code, size_shader);


	GraphicsEngine::get()->releaseCompileShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	pixel_shader = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompileShader();


	Constant constant;
	constant.time = 0;


	constant_buffer = GraphicsEngine::get()->createConstantBuffer();
	constant_buffer->load(&constant, sizeof(constant));
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->swap_chain, 0, 0.2f, 0.6f, 1);

	//set viewport of render target in which we have to draw
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	Constant constant;
	constant.time = ::GetTickCount64();

	constant_buffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &constant);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertex_shader, constant_buffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixel_shader, constant_buffer);

	//Set default shader in the graphics pipeline to be able to draw 
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertex_shader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixel_shader);

	//Set the vertices of the triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertex_buffer);

	// Draw the figure
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vertex_buffer->getSizeVertexList(), 0);


	swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	vertex_buffer->release();
	swap_chain->release();
	pixel_shader->release();
	vertex_shader->release();
	GraphicsEngine::get()->release();
}

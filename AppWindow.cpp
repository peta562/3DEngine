#include "AppWindow.h"

struct Vector3
{
	float x, y, z;
};

struct Vertex
{
	Vector3 position;
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
		{-0.5f, -0.5f, 0.0f}, // pos1
		{-0.5f, 0.5f, 0.0f}, // pos2
		{0.5f, -0.5f, 0.0f}, // pos3
		{0.4f, 0.2f, 0.0f}, // pos4
		//{0.0f, -0.5f, 0.0f}, // pos5
		//{-0.5f, -0.5f, 0.0f} // pos6

	};

	vertex_buffer=GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	vertex_shader = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	vertex_buffer->load(list, sizeof(Vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompileShader();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->swap_chain, 0, 0.2f, 0.6f, 1);

	RECT rc = this->getClientWindowRect();

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->setShaders();
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertex_shader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(vertex_buffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vertex_buffer->getSizeVertexList(), 0);


	swap_chain->present(true);

}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	vertex_buffer->release();
	swap_chain->release();
	GraphicsEngine::get()->release();
}

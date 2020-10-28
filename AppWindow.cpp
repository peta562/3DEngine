#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"



struct Vertex
{
	Vector3D position;
	Vector3D new_position;
	Vector3D color;
	Vector3D new_color;
};

__declspec(align(16)) // because directX stored data in video memory in chanks of 16 bytes
struct Constant
{
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 projection;
	unsigned int time;
};

void AppWindow::updateQuadPosition()
{
	Constant constant;
	Matrix4x4 temp;

	constant.time = ::GetTickCount64();

	delta_pos += delta_time / 4.0f;

	if (delta_pos > 1.0f)
	{
		delta_pos = 0;
	}

	delta_scale += delta_time / 1.0f;

	

	constant.world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(delta_scale) + 1.0f / 2.0f)));
	temp.setTranslation(Vector3D::lerp(Vector3D(-0.5f, -0.5f, 0), Vector3D(0.5f, 0.5f, 0), delta_pos));
	
	constant.world *= temp;

	constant.view.setIdentity();
	constant.projection.setOrtho
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 400.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 400.0f,
		-4.0f,
		4.0f
	);


	constant_buffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &constant);
}

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
		{Vector3D(-0.3f, -0.2f, 0.0f),   Vector3D(-0.25f, -0.11f, 0.0f),   Vector3D(1, 0, 0),   Vector3D(1, 1, 1)}, // pos1  new_pos1   color1  new_color1
		{Vector3D(-0.3f, 0.2f, 0.0f),    Vector3D(-0.77f, 0.78f, 0.0f),    Vector3D(0, 1, 1),   Vector3D(0, 0, 1)}, // pos2  new_pos2   color2  new_color2
		{Vector3D(0.3f, -0.2f, 0.0f),   Vector3D(0.75f, -0.72f, 0.0f),   Vector3D(0, 0, 1),   Vector3D(1, 0, 0)}, // pos3  new_pos3   color3  new_color3
		{Vector3D(0.3f, 0.2f, 0.0f),     Vector3D(0.82f, 0.79f, 0.0f),     Vector3D(1, 1, 1),   Vector3D(0, 0, 1)}, // pos4  new_pos4   color4  new_color4

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
	

	updateQuadPosition();


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


	old_delta = new_delta;
	new_delta = ::GetTickCount64();
	delta_time = (old_delta) ? ((new_delta - old_delta) / 1000.0f) : 0;

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

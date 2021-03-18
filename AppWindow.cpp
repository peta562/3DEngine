#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"



struct Vertex
{
	Vector3D position;
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

	delta_pos += delta_time / 10.0f;

	if (delta_pos > 1.0f)
	{
		delta_pos = 0;
	}

	delta_scale += delta_time / 0.55f;

	

	//constant.world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(delta_scale) + 1.0f / 2.0f)));
	//temp.setTranslation(Vector3D::lerp(Vector3D(-0.5f, -0.5f, 0), Vector3D(0.5f, 0.5f, 0), delta_pos));
	
	//constant.world *= temp;

	constant.world.setScale(Vector3D(scale_cube, scale_cube, scale_cube));

	temp.setIdentity();
	temp.setRotationZ(0.0f);
	constant.world *= temp;

	temp.setIdentity();
	temp.setRotationY(rotation_y);
	constant.world *= temp;

	temp.setIdentity();
	temp.setRotationX(rotation_x);
	constant.world *= temp;

	constant.view.setIdentity();
	constant.projection.setOrtho
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left) / 200.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top) / 200.0f,
		-4.0f,
		4.0f
	);


	constant_buffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &constant);
}

void AppWindow::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);

	GraphicsEngine::get()->init();

	swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();

	swap_chain->init(this->hwnd, rc.right - rc.left, rc.bottom - rc.top);
	

	// {x, y, z} from -1 to 1
	Vertex vertex_list[] =
	{

		// X-Y-Z
		// Front face
		{Vector3D(-0.5f, -0.5f, -0.5f),     Vector3D(1, 0, 0),   Vector3D(1, 1, 1)}, // pos1   color1  new_color1
		{Vector3D(-0.5f, 0.5f, -0.5f),      Vector3D(0, 1, 1),   Vector3D(0, 0, 1)}, // pos2   color2  new_color2
		{Vector3D(0.5f, 0.5f, -0.5f),      Vector3D(0, 0, 1),   Vector3D(1, 0, 0)}, // pos3    color3  new_color3
		{Vector3D(0.5f, -0.5f, -0.5f),       Vector3D(1, 1, 1),   Vector3D(0, 0, 1)}, // pos4   color4  new_color4
		
		//Back face
		{Vector3D(0.5f, -0.5f, 0.5f),     Vector3D(1, 0, 0),   Vector3D(1, 1, 1)}, // pos1   color1  new_color1
		{Vector3D(0.5f, 0.5f, 0.5f),      Vector3D(0, 1, 1),   Vector3D(0, 0, 1)}, // pos2   color2  new_color2
		{Vector3D(-0.5f, 0.5f, 0.5f),      Vector3D(0, 0, 1),   Vector3D(1, 0, 0)}, // pos3    color3  new_color3
		{Vector3D(-0.5f, -0.5f, 0.5f),       Vector3D(1, 1, 1),   Vector3D(0, 0, 1)}, // pos4   color4  new_color4
	};

	vertex_buffer=GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);


	unsigned int index_list[] =
	{
		//front side
		0,1,2,  //1-st triangle
		2,3,0,  //2-st triangle
		//back side
		4,5,6,  //3-st triangle
		6,7,4,  //4-st triangle
		//top side
		1,6,5,
		5,2,1,
		//bottom side
		7,0,3,
		3,4,7,
		//right side
		3,2,5,
		5,4,3,
		//left side
		7,6,1,
		1,0,7
	};

	index_buffer = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	index_buffer->load(index_list, size_index_list);



	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	vertex_shader = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	vertex_buffer->load(vertex_list, sizeof(Vertex), size_list, shader_byte_code, size_shader);

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

	InputSystem::get()->update();

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
	//Set the indixes of the triangle to draw
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(index_buffer);

	// Draw the figure
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexTriangleList(index_buffer->getSizeIndexList(),0, 0);


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
	index_buffer->release();
	constant_buffer->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		rotation_x += delta_time * 0.9f;
	}
	else if (key == 'S')
	{
		rotation_x -= delta_time * 0.9f;
	}
	else if (key == 'A')
	{
		rotation_y += delta_time * 0.9f;
	}
	else if (key == 'D')
	{
		rotation_y -= delta_time * 0.9f;
	}
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
	rotation_x -= delta_mouse_pos.y * delta_time;
	rotation_y -= delta_mouse_pos.x * delta_time;
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	scale_cube = 1;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	scale_cube = 1;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	scale_cube = 2;
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);

}

void AppWindow::onLoseFocus()
{
	InputSystem::get()->removeListener(this);
}

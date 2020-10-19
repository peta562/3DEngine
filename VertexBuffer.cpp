#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer():input_layout(0),buffer(0)
{
}

VertexBuffer::~VertexBuffer()
{
}
// Create the vertex buffer with 3 verticles and input layout
bool VertexBuffer::load(void *list_verticles, UINT size_vrtx, UINT size_lst, void* shader_byte_code, size_t size_byte_shader)
{
	// VertexBuffer::load can be used mulpitle times whith different list of veticles
	if (buffer)
	{
		buffer->Release();
	}
	if (input_layout)
	{
		input_layout->Release();
	}
	
	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT; // read and write by GPU
	buffer_desc.ByteWidth = size_vrtx * size_lst;  //size in bytes of vertex buffer
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_verticles;

	size_vertex = size_vrtx;
	size_list = size_lst;

	HRESULT hr = GraphicsEngine::get()->d3d_device->CreateBuffer(&buffer_desc, &init_data, &buffer);
	if (FAILED(hr))
	{
		return false;
	}

	// info about the attributes what compose vertex type
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// Name - Index - format - input slot - aligned byte offset - input slot class - instance data step rate
		{"POSITION", 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 1 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 1 , DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	UINT size_layout = ARRAYSIZE(layout);

	hr = GraphicsEngine::get()->d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &input_layout);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool VertexBuffer::release()
{
	input_layout->Release();
	buffer->Release();

	delete this;
	return true;
}

UINT VertexBuffer::getSizeVertexList()
{
	return this->size_list;
}

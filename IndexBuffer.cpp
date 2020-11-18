#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer() : buffer(0)
{
}

bool IndexBuffer::load(void* list_indexes, UINT size_lst)
{
	if (buffer)
	{
		buffer->Release();
	}

	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT; // read and write by GPU
	buffer_desc.ByteWidth = 4 * size_lst;  //size in bytes of vertex buffer
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indexes;


	size_list = size_lst;

	HRESULT hr = GraphicsEngine::get()->d3d_device->CreateBuffer(&buffer_desc, &init_data, &buffer);
	if (FAILED(hr))
	{
		return false;
	}

	
	
	return true;
}

bool IndexBuffer::release()
{
	buffer->Release();

	delete this;
	return true;
}

IndexBuffer::~IndexBuffer()
{
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->size_list;
}

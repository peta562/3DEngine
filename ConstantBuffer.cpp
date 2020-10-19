#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
}

bool ConstantBuffer::load(void* buf, UINT size_buffer)
{
	// ConstantBuffer::load can be used mulpitle times whith different list of veticles
	if (buffer)
	{
		buffer->Release();
	}


	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT; // read and write by GPU
	buffer_desc.ByteWidth = size_buffer;  //size in bytes of vertex buffer
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buf;


	HRESULT hr = GraphicsEngine::get()->d3d_device->CreateBuffer(&buffer_desc, &init_data, &buffer);
	if (FAILED(hr))
	{
		return false;
	}


	return true;
}

void ConstantBuffer::update(DeviceContext* context, void* buffer)
{
	context->device_context->UpdateSubresource(this->buffer, NULL, NULL, buffer, NULL, NULL);  // upload the new data into our buffer in video memory
}

bool ConstantBuffer::release()
{
	if (buffer)
	{
		buffer->Release();
	}
	delete this;
	return true;
}

#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"


DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):device_context(device_context)
{
}

DeviceContext::~DeviceContext()
{
	
}

bool DeviceContext::release()
{
	device_context->Release();
	delete this;
	return true;
}

void DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = { red,green,blue,alpha }; //vector of 4 channels of the color

	device_context->ClearRenderTargetView(swap_chain->rtv, clear_color);
	device_context->OMSetRenderTargets(1, &swap_chain->rtv, NULL); //set in which render target we want to draw
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertex_buffer)
{
	UINT sz_vrtx = vertex_buffer->size_vertex;
	UINT offset = 0;
	
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer->buffer, &sz_vrtx, &offset);

	device_context->IASetInputLayout(vertex_buffer->input_layout);

}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::setVertexShader(VertexShader* vertex_shader)
{
	device_context->VSSetShader(vertex_shader->vs, nullptr, 0);
}


void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	device_context->RSSetViewports(1, &viewport);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	device_context->Draw(vertex_count, start_vertex_index);
}


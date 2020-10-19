#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class VertexShader;
class ConstantBuffer;
class PixelShader;

/*	Device Context allow us to generate the rendering commands to the video driver 
	for the execution
	The driver then will redirect the commands to
	the GPU or the CPU for the elaborationand the final rendering on the screen
*/

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	~DeviceContext();
	
	bool release();
	void clearRenderTargetColor(SwapChain* swap_chain,float red, float green, float blue, float alpha);
	
	void setVertexBuffer(VertexBuffer* vertex_buffer);

	void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* constant_buffer);
	void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* constant_buffer);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setViewportSize(UINT width, UINT height);  //Set a viewport of a render target
	
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index); //A triangular stripe is a series of connected triangles in a triangular mesh that separate vertices.
	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);

	
private:
	ID3D11DeviceContext* device_context;
	friend class ConstantBuffer;
};


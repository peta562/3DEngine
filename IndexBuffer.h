#pragma once
#include <d3d11.h>

class DeviceContext;

class IndexBuffer
{
public:
	IndexBuffer();

	bool load(void* list_indexes, UINT size_lst);
	bool release();

	~IndexBuffer();

	UINT getSizeIndexList();
private:
	UINT size_list;
	ID3D11Buffer* buffer;  
private:
	friend class DeviceContext;
};


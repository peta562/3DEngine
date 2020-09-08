#pragma once
#include <d3d11.h>

class DeviceContext;

// Class for loading and keeping list of vericles and them parameters

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    bool load(void* list_vericles, UINT size_vrtx, UINT size_lst, void* shader_byte_code, size_t size_byte_shader);
    bool release();

    UINT getSizeVertexList();
private:
    UINT size_vertex;
    UINT size_list;
    ID3D11Buffer* buffer;
    ID3D11InputLayout* input_layout;  // object keeping attributes of vertex type: names, size in bytes etc
private:
    friend class DeviceContext;
};


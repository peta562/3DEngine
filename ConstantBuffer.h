#pragma once
#include <d3d11.h>

class DeviceContext;


/* Constant buffer used to get the execution time 
of one frame and the past position */

class ConstantBuffer
{
public:
    ConstantBuffer();
    ~ConstantBuffer();
    
    bool load(void* buf, UINT size_buffer);
    void update(DeviceContext* context, void* buffer);
    bool release();

private:
    ID3D11Buffer* buffer;
private:
    friend class DeviceContext;
};


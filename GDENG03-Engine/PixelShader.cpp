#include "PixelShader.h"
#include "GraphicsEngine.h"


PixelShader::PixelShader()
{
}

void PixelShader::release()
{
	if(m_ps)
		m_ps->Release();
	delete this;
}

ID3D11PixelShader* PixelShader::getShader()
{
	return this->m_ps;
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		return false;

	return true;
}



PixelShader::~PixelShader()
{
}
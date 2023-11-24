#include "VertexShader.h"
#include "GraphicsEngine.h"


VertexShader::VertexShader()
{
}

void VertexShader::release()
{
	if (m_vs)
		m_vs->Release();
	delete this;
}

ID3D11VertexShader* VertexShader::getShader()
{
	return this->m_vs;
}

bool VertexShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (FAILED(GraphicsEngine::get()->getDirectD3D11Device()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs))) {
		return false;
	}

	return true;
}



VertexShader::~VertexShader()
{
}
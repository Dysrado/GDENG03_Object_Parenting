#include "TexturedVertexBuffer.h"
#include "GraphicsEngine.h"
#include <iostream>

TexturedVertexBuffer::TexturedVertexBuffer() : VertexBuffer()
{
}

TexturedVertexBuffer::~TexturedVertexBuffer()
{
	VertexBuffer::~VertexBuffer();
}

bool TexturedVertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	//release if previous buffer and input layout are used from previous frame update.
	if (this->m_buffer!= NULL) {
		this->m_buffer->Release();
	}

	if (this->m_layout != NULL) {
		this->m_layout->Release();
	}

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = size_vertex * size_list;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;

	ID3D11Device* directXDevice = GraphicsEngine::get()->getDirectD3D11Device();
	HRESULT bufferResult = directXDevice->CreateBuffer(&bufferDesc, &initData, &this->m_buffer);
	if (SUCCEEDED(bufferResult)) {
		std::cout << "Creation of textured buffer succeeded. \n";
	}
	else {
		std::cout << "An error occurred in creating a textured buffer. \n";
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		//semantic name - index, format, input slot, aligned byte offset, input slot class, instance data step rate
		//2 bytes each entry
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT layoutSize = ARRAYSIZE(layout);
	HRESULT layoutResult = directXDevice->CreateInputLayout(layout, layoutSize, shader_byte_code, size_byte_shader, &this->m_layout);
	if (SUCCEEDED(layoutResult)) {
		std::cout << "Creation of input layout succeeded. \n";
	}
	else {
		std::cout << "An error occurred in creating an input layout. \n";
	}
	return true;
}

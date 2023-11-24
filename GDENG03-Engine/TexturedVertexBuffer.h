#pragma once
#include "VertexBuffer.h"
class TexturedVertexBuffer : public VertexBuffer
{
public:
	TexturedVertexBuffer();
	~TexturedVertexBuffer();

	bool load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader) override;
};


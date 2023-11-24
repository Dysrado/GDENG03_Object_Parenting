#pragma once
#include "Cube.h"
#include "TexturedVertexBuffer.h"
#include "Vector2D.h"

class TexturedCube : public Cube
{
public:
	TexturedCube(std::string name);
	~TexturedCube();

	void draw(int width, int height) override;

protected:
	TexturedVertexBuffer* vertexBuffer;
private:
	struct Vertex {
		Vector3D position;
		Vector2D texCoord;
	};
};


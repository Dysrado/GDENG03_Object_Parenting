#pragma once
#include "Cube.h"
#include "TexturedVertexBuffer.h"
#include "Vector2D.h"

class ObjectRenderer;
class TexturedCube : public Cube
{
public:
	TexturedCube(std::string name);
	~TexturedCube();

	void attachRenderer(ObjectRenderer* renderer);
	void draw(int width, int height) override;
	ObjectRenderer* getRenderer() const;

protected:
	TexturedVertexBuffer* vertexBuffer;
private:
	struct Vertex2 {
		Vector3D position;
		Vector2D texCoord;
	};

	ObjectRenderer* renderer;
};


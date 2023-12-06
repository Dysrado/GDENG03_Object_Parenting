#pragma once
#include <string>

#include "Texture.h"

class ObjectRenderer
{
protected:
	typedef std::string String;

public:
	void setRenderer(std::string path);
	std::string getMaterialPath() const;
	Texture* getTexture() const;

private:
	std::string materialPath;
	Texture* texture = nullptr;
};


#include "ObjectRenderer.h"

#include "TextureManager.h"
#include  <filesystem>

void ObjectRenderer::setRenderer(std::string path)
{
	this->materialPath = path;
	std::wstring wPath = std::filesystem::absolute(materialPath);//std::wstring(materialPath.begin(), materialPath.end());
	const wchar_t* texturePath = wPath.c_str();
	this->texture = TextureManager::getInstance()->createTextureFromFile(texturePath);
}

std::string ObjectRenderer::getMaterialPath() const
{
	return materialPath;
}

Texture* ObjectRenderer::getTexture() const
{
	return texture;
}

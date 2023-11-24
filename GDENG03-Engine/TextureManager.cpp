#include "TextureManager.h"
#include "Texture.h"
#include <filesystem>

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::initialize()
{
	sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
	delete sharedInstance;
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

Texture* TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	// Get the full path
	wchar_t buffer[MAX_PATH];
	GetFullPathName(filePath, MAX_PATH, buffer, nullptr);

	if (this->resourceMap[buffer] == NULL) {
		std::cout << " null .." << std::endl;
		this->resourceMap[buffer] = this->convertToResource(filePath);
	}

	return (Texture*)this->resourceMap[buffer];
}

TextureManager::TextureManager() :AResourceManager()
{

}

TextureManager::~TextureManager()
{
	AResourceManager::~AResourceManager();
}

Resource* TextureManager::convertToResource(const wchar_t* filePath)
{
	Texture* tex = NULL;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...)
	{
		
	}

	return (Resource*)tex;
}

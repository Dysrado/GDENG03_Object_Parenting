#pragma once
#include <string>
class SceneWriter
{
public:
	typedef std::string String;

	void setDirectory(String directory);
	void writeToFile();

private:
	String directory;

};


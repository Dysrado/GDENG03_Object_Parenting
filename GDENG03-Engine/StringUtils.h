#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
class StringUtils {
public:
	static std::vector<std::string> split(const std::string& input, char delimiter)
	{
		std::stringstream ss(input);
		std::string item;
		std::vector<std::string> elems;
		while (std::getline(ss, item, delimiter)) 
		{
			elems.push_back(item);
		}
		return elems;
	}
};
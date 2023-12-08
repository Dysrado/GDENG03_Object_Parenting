#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"




class UINames
{
public:
	typedef std::string String;

	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const String MATERIAL_SCREEN = "MATERIAL_SCREEN";
};

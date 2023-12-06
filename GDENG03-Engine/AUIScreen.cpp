#include "AUIScreen.h"

AUIScreen::AUIScreen(String name)
{
	this->name = name;
	isEnabled = true;
}

AUIScreen::~AUIScreen()
{
}

void AUIScreen::setEnabled(bool flag)
{
	isEnabled = flag;
}

AUIScreen::String AUIScreen::getName()
{
	return this->name;
}

void AUIScreen::drawUI()
{
}

bool AUIScreen::getEnabled()
{
	return isEnabled;
}

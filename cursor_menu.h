#pragma once
#include <string>

void setCursorPos(int y);
int showMenu(const std::string& title, const std::string opts[], int count, bool rememberPosition = false);
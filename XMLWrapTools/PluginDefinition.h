//this file is part of XMLWrapTools Plugin for Notepad++
//Copyright (C)2024
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef PLUGINDEFINITION_H
#define PLUGINDEFINITION_H

#include "PluginInterface.h"

const TCHAR NPP_PLUGIN_NAME[] = TEXT("XML Wrap Tools");

const int nbFunc = 7;

FuncItem funcItem[nbFunc];

NppData nppData;

HINSTANCE _hInst;

// Array to store toolbar icon handles for cleanup
HBITMAP _toolbarIcons[7] = {NULL};

void pluginInit(HANDLE hModule);
void pluginCleanUp();
void commandMenuInit();
void commandMenuCleanUp();
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool checkOnInit = false);

// Plugin command functions
void func_wrapHead();
void func_wrapTitle();
void func_wrapHi();
void func_wrapQuote();
void func_wrapTrailer();
void func_wrapForeign();
void func_wrapSerbianQuotes();

#endif //PLUGINDEFINITION_H

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

#ifndef XMLWRAPTOOLS_H
#define XMLWRAPTOOLS_H

#include <windows.h>
#include <string>

// Helper function to wrap selected text with prefix and suffix
void wrapSelection(const std::wstring& prefix, const std::wstring& suffix);

#endif //XMLWRAPTOOLS_H

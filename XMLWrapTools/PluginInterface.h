//this file is part of notepad++
//Copyright (C)2022 Don HO <don.h@free.fr>
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
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include "Notepad_plus_msgs.h"
#include "Scintilla.h"

struct NppData {
	HWND _nppHandle;
	HWND _scintillaMainHandle;
	HWND _scintillaSecondHandle;
};

struct ShortcutKey {
	bool _isCtrl;
	bool _isAlt;
	bool _isShift;
	UCHAR _key;
};

typedef void (*PFUNCPLUGINCMD)(void);

struct FuncItem {
	TCHAR _itemName[64];
	PFUNCPLUGINCMD _pFunc;
	int _cmdID;
	bool _init2Check;
	ShortcutKey* _pShKey;
};

typedef void (*PFUNCSETINFO)(NppData);
typedef void (*PBENOTIFIED)(SCNotification *);
typedef LRESULT (*PMESSAGEPROC)(UINT Message, WPARAM wParam, LPARAM lParam);

#endif //PLUGIN_INTERFACE_H

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

#include "PluginDefinition.h"
#include "XMLWrapTools.h"
#include "resource.h"

extern FuncItem funcItem[nbFunc];
extern NppData nppData;

BOOL APIENTRY DllMain(HANDLE hModule, DWORD reasonForCall, LPVOID /*lpReserved*/)
{
    switch (reasonForCall)
    {
        case DLL_PROCESS_ATTACH:
            _hInst = (HINSTANCE)hModule;
            pluginInit(hModule);
            break;

        case DLL_PROCESS_DETACH:
            commandMenuCleanUp();
            pluginCleanUp();
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}

extern "C" __declspec(dllexport) void setInfo(NppData notpadPlusData)
{
    nppData = notpadPlusData;
    commandMenuInit();
}

extern "C" __declspec(dllexport) const TCHAR * getName()
{
    return NPP_PLUGIN_NAME;
}

extern "C" __declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
    *nbF = nbFunc;
    return funcItem;
}

extern "C" __declspec(dllexport) void beNotified(SCNotification *notifyCode)
{
    switch (notifyCode->nmhdr.code)
    {
        case NPPN_TBMODIFICATION:
        {
            // Helper function to add a single toolbar icon
            auto addToolbarIcon = [](int resourceId, int cmdIndex) {
                HBITMAP hBitmap = (HBITMAP)::LoadImage(_hInst, MAKEINTRESOURCE(resourceId), 
                                                       IMAGE_BITMAP, 16, 16, LR_LOADMAP3DCOLORS);
                if (hBitmap)
                {
                    toolbarIconsWithDarkMode icon;
                    icon.hToolbarBmp = hBitmap;
                    icon.hToolbarIcon = hBitmap;
                    icon.hToolbarIconDarkMode = hBitmap;
                    ::SendMessage(nppData._nppHandle, NPPM_ADDTOOLBARICON_FORDARKMODE, 
                                 (WPARAM)funcItem[cmdIndex]._cmdID, (LPARAM)&icon);
                }
            };

            // Add toolbar icons for all commands
            addToolbarIcon(IDB_HEAD, 0);
            addToolbarIcon(IDB_TITLE, 1);
            addToolbarIcon(IDB_HI, 2);
            addToolbarIcon(IDB_QUOTE, 3);
            addToolbarIcon(IDB_TRAILER, 4);
            addToolbarIcon(IDB_FOREIGN, 5);
            addToolbarIcon(IDB_SERBIAN_QUOTES, 6);
        }
        break;

        case NPPN_SHUTDOWN:
        {
            commandMenuCleanUp();
        }
        break;

        default:
            return;
    }
}

extern "C" __declspec(dllexport) LRESULT messageProc(UINT /*Message*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    return TRUE;
}

#ifdef UNICODE
extern "C" __declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}
#endif

void pluginInit(HANDLE /*hModule*/)
{
}

void pluginCleanUp()
{
}

void commandMenuInit()
{
    setCommand(0, TEXT("Wrap as <head>"), func_wrapHead, NULL, false);
    setCommand(1, TEXT("Wrap as <title>"), func_wrapTitle, NULL, false);
    setCommand(2, TEXT("Wrap as <hi>"), func_wrapHi, NULL, false);
    setCommand(3, TEXT("Wrap as <quote>"), func_wrapQuote, NULL, false);
    setCommand(4, TEXT("Wrap as <trailer>"), func_wrapTrailer, NULL, false);
    setCommand(5, TEXT("Wrap as <foreign>"), func_wrapForeign, NULL, false);
    setCommand(6, TEXT("Wrap with Serbian quotes"), func_wrapSerbianQuotes, NULL, false);
}

void commandMenuCleanUp()
{
}

bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit)
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;
    return true;
}

// Command implementations
void func_wrapHead()
{
    wrapSelection(L"<head>", L"</head>");
}

void func_wrapTitle()
{
    wrapSelection(L"<title>", L"</title>");
}

void func_wrapHi()
{
    wrapSelection(L"<hi>", L"</hi>");
}

void func_wrapQuote()
{
    wrapSelection(L"<quote>", L"</quote>");
}

void func_wrapTrailer()
{
    wrapSelection(L"<trailer>", L"</trailer>");
}

void func_wrapForeign()
{
    wrapSelection(L"<foreign xml:lang=\"en\">", L"</foreign>");
}

void func_wrapSerbianQuotes()
{
    wrapSelection(L"\u201E", L"\u201C");
}

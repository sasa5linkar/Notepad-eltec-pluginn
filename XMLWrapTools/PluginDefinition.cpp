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

/**
 * @brief Handles DLL lifetime events and invokes plugin initialization and cleanup.
 *
 * Responds to process attach and detach notifications by storing the module
 * handle and calling pluginInit on attach, and by calling commandMenuCleanUp
 * and pluginCleanUp on detach. Thread attach/detach notifications are ignored.
 *
 * @param hModule Handle to the DLL module.
 * @param reasonForCall Reason code indicating why the entry-point is being called (e.g., DLL_PROCESS_ATTACH, DLL_PROCESS_DETACH).
 * @param lpReserved Reserved; not used.
 * @return BOOL `TRUE` on successful handling of the notification.
 */
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

extern "C" /**
 * @brief Stores Notepad++ host data and initializes the plugin's command menu.
 *
 * @param notepadPlusData Structure provided by Notepad++ containing handles and references the plugin needs (saved to the module-global `nppData`).
 */
__declspec(dllexport) void setInfo(NppData notepadPlusData)
{
    nppData = notepadPlusData;
    commandMenuInit();
}

extern "C" /**
 * @brief Provide the plugin name used by Notepad++.
 *
 * @return Pointer to a null-terminated string containing the plugin name.
 */
__declspec(dllexport) const TCHAR * getName()
{
    return NPP_PLUGIN_NAME;
}

extern "C" /**
 * @brief Exposes the plugin's command table and provides its length.
 *
 * @param nbF Pointer to an int that will be set to the number of commands in the returned array.
 * @return FuncItem* Pointer to the first element of the plugin's command array.
 */
__declspec(dllexport) FuncItem * getFuncsArray(int *nbF)
{
    *nbF = nbFunc;
    return funcItem;
}

extern "C" /**
 * @brief Handle Notepad++ notifications relevant to the plugin lifecycle and toolbar.
 *
 * Processes notification codes to perform plugin-specific actions:
 * - On TBMODIFICATION: loads 16x16 bitmap resources for each registered command and registers them with Notepad++ (including dark-mode variants) to add toolbar icons.
 * - On SHUTDOWN: runs plugin command cleanup.
 *
 * @param notifyCode Pointer to the SCNotification provided by Notepad++ describing the event.
 */
__declspec(dllexport) void beNotified(SCNotification *notifyCode)
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
                    // Store the handle for cleanup later
                    _toolbarIcons[cmdIndex] = hBitmap;
                    
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

extern "C" /**
 * @brief Default message handler that consumes all messages without processing.
 *
 * This stub always reports the message as handled and performs no side effects.
 *
 * @return LRESULT Non-zero (`TRUE`) indicating the message was handled. 
 */
__declspec(dllexport) LRESULT messageProc(UINT /*Message*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    return TRUE;
}

#ifdef UNICODE
extern "C" /**
 * @brief Signals that the plugin is Unicode-aware to the host application.
 *
 * Returns the plugin's expectation for the Notepad++ API character encoding.
 *
 * @return TRUE if the plugin expects the Unicode Notepad++ API, FALSE otherwise.
 */
__declspec(dllexport) BOOL isUnicode()
{
    return TRUE;
}
#endif

/**
 * @brief Initialize plugin state when the plugin is loaded.
 *
 * This hook is invoked on DLL process attach to perform plugin-specific
 * initialization. Currently a no-op.
 */
void pluginInit(HANDLE /*hModule*/)
{
}

/**
 * @brief Perform plugin shutdown and release resources before unload.
 *
 * Releases any allocated resources (including toolbar icon bitmaps) and performs
 * teardown required when the plugin is being unloaded (for example on DLL process detach).
 */
void pluginCleanUp()
{
    // Release toolbar icon bitmaps
    for (int i = 0; i < 7; i++)
    {
        if (_toolbarIcons[i])
        {
            ::DeleteObject(_toolbarIcons[i]);
            _toolbarIcons[i] = NULL;
        }
    }
}

/**
 * @brief Register the plugin's wrap commands in the Notepad++ command menu.
 *
 * Adds menu entries and binds each to its handler for wrapping the current selection:
 * "Wrap as <head>", "Wrap as <title>", "Wrap as <hi>", "Wrap as <quote>",
 * "Wrap as <trailer>", "Wrap as <foreign>", and "Wrap with Serbian quotes".
 */
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

/**
 * @brief Clean up plugin command menu and release related resources.
 *
 * Called during plugin shutdown to remove registered commands, free any
 * menu-related resources, and perform final command-table cleanup.
 */
void commandMenuCleanUp()
{
}

/**
 * @brief Registers a plugin command into the plugin's command table at the given index.
 *
 * Stores the command name, callback, shortcut key and initial-checked flag into the internal FuncItem array.
 *
 * @param index Destination index in the command table; must be less than `nbFunc`.
 * @param cmdName Null-terminated string to display as the command name in the menu/toolbar.
 * @param pFunc Pointer to the command callback function.
 * @param sk Optional pointer to a ShortcutKey structure for the command; may be null.
 * @param checkOnInit If true, the command will be marked checked on initialization.
 * @return true if the command was registered successfully, false if `index` is out of range or `pFunc` is null.
 */
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool checkOnInit)
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = checkOnInit;
    funcItem[index]._pShKey = sk;
    return true;
}

/**
 * @brief Wraps the current editor selection with <head> tags.
 *
 * Inserts an opening `<head>` tag before the selection and a closing `</head>` tag after it.
 */
void func_wrapHead()
{
    wrapSelection(L"<head>", L"</head>");
}

/**
 * @brief Wraps the current selection with <title> and </title> tags.
 */
void func_wrapTitle()
{
    wrapSelection(L"<title>", L"</title>");
}

/**
 * @brief Wraps the current selection with <hi> and </hi> tags.
 *
 * Surrounds whatever text is currently selected in the editor with the opening tag `<hi>`
 * and the corresponding closing tag `</hi>`.
 */
void func_wrapHi()
{
    wrapSelection(L"<hi>", L"</hi>");
}

/**
 * @brief Surrounds the current selection with XML <quote> start and end tags.
 *
 * If there is no selection, inserts an empty `<quote></quote>` pair at the caret.
 */
void func_wrapQuote()
{
    wrapSelection(L"<quote>", L"</quote>");
}

/**
 * @brief Surrounds the current editor selection with XML <trailer> tags.
 *
 * Wraps the selected text (or inserts tags at the caret if no selection) using opening `<trailer>` and closing `</trailer>` tags.
 */
void func_wrapTrailer()
{
    wrapSelection(L"<trailer>", L"</trailer>");
}

/**
 * @brief Wraps the current selection with a <foreign xml:lang="en"> element.
 *
 * Surrounds the current editor selection with an opening `<foreign xml:lang="en">` tag and a closing `</foreign>` tag.
 */
void func_wrapForeign()
{
    wrapSelection(L"<foreign xml:lang=\"en\">", L"</foreign>");
}

/**
 * @brief Wraps the current selection with Serbian-style quotation marks.
 *
 * Surrounds the selection with U+201E (left double low-9 quotation mark) as
 * the opening quote and U+201C (left double quotation mark) as the closing quote.
 */
void func_wrapSerbianQuotes()
{
    wrapSelection(L"\u201E", L"\u201C");
}
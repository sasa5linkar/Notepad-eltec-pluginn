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

#include "XMLWrapTools.h"
#include "PluginDefinition.h"
#include "Scintilla.h"
#include <string>
#include <new>

extern NppData nppData;

/**
 * @brief Retrieves the handle of the active Scintilla editor.
 *
 * Queries Notepad++ to determine which Scintilla view is active and returns
 * the corresponding window handle.
 *
 * @return HWND Handle to the active Scintilla: the main view handle if the primary view is active, otherwise the secondary view handle.
 */
HWND getCurrentScintilla()
{
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    return (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
}

/**
 * @brief Converts a wide-character string to a UTF-8 encoded byte string.
 *
 * @param wstr Wide string to convert.
 * @return std::string UTF-8 encoded representation of `wstr`; returns an empty string if `wstr` is empty.
 */
std::string wstringToUtf8(const std::wstring& wstr)
{
    if (wstr.empty()) return std::string();
    
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

/**
 * @brief Converts a UTF-8 encoded std::string to a std::wstring.
 *
 * @param str UTF-8 encoded input string.
 * @return std::wstring Converted wide string (UTF-16 on Windows). Returns an empty std::wstring if `str` is empty.
 */
std::wstring utf8ToWstring(const std::string& str)
{
    if (str.empty()) return std::wstring();
    
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), &wstrTo[0], size_needed);
    return wstrTo;
}

/****
 * @brief Wraps the current Scintilla selection with the provided prefix and suffix.
 *
 * If no text is selected, displays an informational message box and returns without modifying the document.
 * When a selection exists, replaces it with prefix + selectedText + suffix and groups the change into a single undo action.
 *
 * @param prefix Wide-string to insert before the selected text.
 * @param suffix Wide-string to insert after the selected text.
 */
void wrapSelection(const std::wstring& prefix, const std::wstring& suffix)
{
    HWND curScintilla = getCurrentScintilla();
    
    // Get selection start and end positions
    long selStart = (long)::SendMessage(curScintilla, SCI_GETSELECTIONSTART, 0, 0);
    long selEnd = (long)::SendMessage(curScintilla, SCI_GETSELECTIONEND, 0, 0);
    
    // Check if there's a selection
    if (selStart == selEnd)
    {
        ::MessageBox(nppData._nppHandle, TEXT("No text selected."), TEXT("XML Wrap Tools"), MB_OK | MB_ICONINFORMATION);
        return;
    }
    
    // Get the selected text
    long selLength = selEnd - selStart;
    char* selectedText = nullptr;
    
    try
    {
        selectedText = new char[selLength + 1];
    }
    catch (const std::bad_alloc&)
    {
        ::MessageBox(nppData._nppHandle, TEXT("Memory allocation failed."), TEXT("XML Wrap Tools"), MB_OK | MB_ICONERROR);
        return;
    }
    
    Sci_TextRange tr;
    tr.chrg.cpMin = selStart;
    tr.chrg.cpMax = selEnd;
    tr.lpstrText = selectedText;
    
    ::SendMessage(curScintilla, SCI_GETTEXTRANGE, 0, (LPARAM)&tr);
    selectedText[selLength] = '\0';
    
    // Convert selected text to wide string
    std::wstring selectedWStr = utf8ToWstring(std::string(selectedText));
    delete[] selectedText;
    
    // Build the new text with wrapping
    std::wstring newText = prefix + selectedWStr + suffix;
    
    // Convert back to UTF-8 for Scintilla
    std::string newTextUtf8 = wstringToUtf8(newText);
    
    // Begin undo action for grouping
    ::SendMessage(curScintilla, SCI_BEGINUNDOACTION, 0, 0);
    
    // Replace the selection with the wrapped text
    ::SendMessage(curScintilla, SCI_REPLACESEL, 0, (LPARAM)newTextUtf8.c_str());
    
    // End undo action
    ::SendMessage(curScintilla, SCI_ENDUNDOACTION, 0, 0);
}
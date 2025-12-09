// Scintilla source code edit control
// ScintillaMessages.h - Simplified header with essential messages for plugin
// Copyright 1998-2022 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef SCINTILLA_H
#define SCINTILLA_H

typedef sptr_t (*SciFnDirect)(sptr_t ptr, unsigned int iMessage, uptr_t wParam, sptr_t lParam);

// Scintilla messages
#define SCI_START 2000
#define SCI_OPTIONAL_START 3000
#define SCI_LEXER_START 4000

#define SCI_GETTEXT 2182
#define SCI_SETTEXT 2181
#define SCI_GETLENGTH 2006
#define SCI_REPLACESEL 2170
#define SCI_GETSELTEXT 2161
#define SCI_GETCURRENTPOS 2008
#define SCI_SETSEL 2160
#define SCI_GOTOPOS 2025
#define SCI_GETCURLINE 2027
#define SCI_GETSELECTIONSTART 2143
#define SCI_GETSELECTIONEND 2145
#define SCI_SETSELECTIONSTART 2142
#define SCI_SETSELECTIONEND 2144
#define SCI_GETLINECOUNT 2154
#define SCI_GETLINE 2153
#define SCI_GETCOLUMN 2129
#define SCI_FINDCOLUMN 2456
#define SCI_POSITIONFROMLINE 2167
#define SCI_LINEFROMPOSITION 2166
#define SCI_GETLINEENDPOSITION 2136
#define SCI_LINELENGTH 2350

#define SCI_GETTEXTRANGE 2162
struct Sci_TextRange {
	struct Sci_CharacterRange {
		long cpMin;
		long cpMax;
	} chrg;
	char *lpstrText;
};

#define SCI_BEGINUNDOACTION 2078
#define SCI_ENDUNDOACTION 2079

#define SCI_GETCODEPAGE 2137
#define SCI_SETCODEPAGE 2037
#define SC_CP_UTF8 65001

#define SCI_SETTARGETSTART 2190
#define SCI_SETTARGETEND 2192
#define SCI_REPLACETARGET 2194
#define SCI_REPLACETARGETRE 2195

#define SCI_SEARCHINTARGET 2197

#define SCI_GETANCHOR 2209
#define SCI_SETANCHOR 2026

#define SCI_GETTEXTLENGTH 2183

#define SCI_GETSELECTIONMODE 2422
#define SCI_SETSELECTIONMODE 2423

#define SC_SEL_STREAM 0
#define SC_SEL_RECTANGLE 1
#define SC_SEL_LINES 2
#define SC_SEL_THIN 3

#define SCI_GETDIRECTFUNCTION 2184
#define SCI_GETDIRECTPOINTER 2185

#define SCI_SETFOCUS 2380

#endif

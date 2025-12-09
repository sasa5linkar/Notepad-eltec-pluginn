# XMLWrapTools - Notepad++ Plugin

A native C++ plugin for Notepad++ that provides quick XML tag wrapping and Serbian quote formatting for selected text.

## Features

XMLWrapTools adds a new menu "XML Wrap Tools" to Notepad++ with 7 commands for wrapping selected text:

1. **Wrap as `<head>`** - Wraps selection with `<head>...</head>`
2. **Wrap as `<title>`** - Wraps selection with `<title>...</title>`
3. **Wrap as `<hi>`** - Wraps selection with `<hi>...</hi>`
4. **Wrap as `<quote>`** - Wraps selection with `<quote>...</quote>`
5. **Wrap as `<trailer>`** - Wraps selection with `<trailer>...</trailer>`
6. **Wrap as `<foreign>`** - Wraps selection with `<foreign xml:lang="en">...</foreign>`
7. **Wrap with Serbian quotes** - Wraps selection with Serbian quotation marks: „selection" (U+201E opening, U+201C closing)

Each command also has a corresponding toolbar icon for quick access.

## Building from Source

### Prerequisites

- **Visual Studio 2022** (Community, Professional, or Enterprise)
- **Windows 10 SDK** (included with Visual Studio)
- **C++ Desktop Development Workload** (installed via Visual Studio Installer)

### Build Steps

1. Clone this repository:
   ```bash
   git clone https://github.com/sasa5linkar/Notepad-eltec-pluginn.git
   cd Notepad-eltec-pluginn
   ```

2. Open the solution in Visual Studio 2022:
   ```
   XMLWrapTools.sln
   ```

3. Select your build configuration:
   - **Debug|x64** - For debugging with symbols
   - **Release|x64** - For optimized production build

4. Build the solution:
   - Press `F7` or use **Build → Build Solution** from the menu
   - The DLL will be created in `x64\Debug\` or `x64\Release\` depending on your configuration

5. The compiled plugin DLL will be named `XMLWrapTools.dll`

### Build Output

After a successful build, you'll find:
- `x64\Release\XMLWrapTools.dll` - The plugin DLL (Release build)
- `x64\Debug\XMLWrapTools.dll` - The plugin DLL with debug symbols (Debug build)

## Installation

### Method 1: Manual Installation

1. **Build the plugin** (see "Building from Source" above) or download a pre-built DLL

2. **Locate your Notepad++ plugins directory:**
   - For Notepad++ 7.6 and later: `C:\Program Files\Notepad++\plugins\XMLWrapTools\`
   - For portable Notepad++: `[Notepad++ folder]\plugins\XMLWrapTools\`

3. **Create the plugin folder structure:**
   ```
   plugins\
   └── XMLWrapTools\
       └── XMLWrapTools.dll
   ```

4. **Copy the DLL:**
   - Copy `XMLWrapTools.dll` from `x64\Release\` to `plugins\XMLWrapTools\`

5. **Restart Notepad++**

### Method 2: Using Notepad++ Plugins Admin (Future)

When this plugin is published to the Notepad++ Plugin Central, you'll be able to install it via:
- **Plugins → Plugins Admin → Available tab**
- Search for "XMLWrapTools" and click Install

## Usage

After installation and restarting Notepad++, you'll see:

1. **New Menu**: "XML Wrap Tools" in the main Plugins menu
2. **Toolbar Icons**: 7 new toolbar buttons (can be customized in Notepad++ settings)

### How to Use

1. **Select text** in your document that you want to wrap
2. **Click** the appropriate toolbar icon or menu item
3. The selected text will be instantly wrapped with the corresponding tags/quotes

### Examples

**Wrapping with XML tags:**
```
Before: This is important text
After (using "Wrap as <hi>"): <hi>This is important text</hi>
```

**Wrapping with Serbian quotes:**
```
Before: Добар дан
After (using "Wrap with Serbian quotes"): „Добар дан"
```

**Wrapping with foreign tag:**
```
Before: Hello World
After (using "Wrap as <foreign>"): <foreign xml:lang="en">Hello World</foreign>
```

### No Selection Behavior

If no text is selected, clicking any wrap command will show a message box:
```
"No text selected."
```

### Undo Support

All wrapping operations are grouped as a single undo action. Press `Ctrl+Z` to undo the wrapping.

## Technical Details

### Plugin Architecture

- **Language**: Native C++ (C++17)
- **Framework**: Notepad++ Plugin API
- **Editor API**: Scintilla messaging
- **Character Encoding**: UTF-8 (supports Unicode text)
- **Build System**: Visual Studio 2022 MSBuild

### Key Features

- ✅ **Fully standalone** - No Python, no external dependencies
- ✅ **Unicode support** - Works with all Unicode characters including Serbian Cyrillic
- ✅ **Undo/Redo support** - All operations are properly grouped
- ✅ **Fast and lightweight** - Native C++ performance
- ✅ **Toolbar integration** - Custom icons for quick access
- ✅ **Dark mode compatible** - Icons work in both light and dark themes

### File Structure

```
XMLWrapTools/
├── PluginDefinition.h         - Plugin interface definitions
├── PluginDefinition.cpp       - Plugin registration and menu commands
├── XMLWrapTools.h             - Helper function declarations
├── XMLWrapTools.cpp           - Core wrapping logic and Scintilla integration
├── resource.h                 - Resource identifiers
├── XMLWrapTools.rc            - Resource script (icons, version info)
├── Scintilla.h                - Scintilla API definitions
├── PluginInterface.h          - Notepad++ plugin interface
├── Notepad_plus_msgs.h        - Notepad++ message definitions
└── icons/                     - Toolbar icon bitmaps
    ├── head.bmp
    ├── title.bmp
    ├── hi.bmp
    ├── quote.bmp
    ├── trailer.bmp
    ├── foreign.bmp
    └── serbian_quotes.bmp
```

## Troubleshooting

### Plugin doesn't appear in Notepad++

1. Verify the DLL is in the correct location: `plugins\XMLWrapTools\XMLWrapTools.dll`
2. Check that you're using a compatible Notepad++ version (7.6 or later recommended)
3. Make sure the DLL is not blocked by Windows (Right-click → Properties → Unblock)
4. Try running Notepad++ as administrator

### "No text selected" message appears when text is selected

1. Make sure you're using the current edit view (not searching in another view)
2. Verify the text is actually highlighted/selected
3. Try clicking in the editor before selecting text

### Build errors in Visual Studio

1. Ensure you have the C++ Desktop Development workload installed
2. Select the x64 platform (not Win32)
3. Make sure Windows SDK is installed
4. Try cleaning and rebuilding: **Build → Clean Solution**, then **Build → Rebuild Solution**

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests.

### Development Setup

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly with different text selections
5. Submit a pull request

## License

This project is licensed under the MIT License.

```
MIT License

Copyright (c) 2024 XMLWrapTools

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Acknowledgments

- Notepad++ team for the excellent plugin API
- Scintilla project for the powerful editor component

## Version History

### Version 1.0.0 (Initial Release)
- Initial release with 7 wrapping commands
- XML tag wrapping: head, title, hi, quote, trailer, foreign
- Serbian quote support
- Toolbar icons
- Full Unicode support
- Undo/Redo support
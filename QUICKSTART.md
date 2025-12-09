# Quick Start Guide - XMLWrapTools

## For Developers

### Building the Plugin

1. **Prerequisites:**
   - Visual Studio 2022 (Community Edition or higher)
   - Windows 10 SDK

2. **Build Steps:**
   ```bash
   # Clone the repository
   git clone https://github.com/sasa5linkar/Notepad-eltec-pluginn.git
   cd Notepad-eltec-pluginn
   
   # Open the solution
   start XMLWrapTools.sln
   ```

3. **In Visual Studio:**
   - Select **Release** configuration and **x64** platform
   - Build → Build Solution (F7)
   - Output: `x64\Release\XMLWrapTools.dll`

### Installation

1. Copy the DLL to Notepad++ plugins directory:
   ```
   C:\Program Files\Notepad++\plugins\XMLWrapTools\XMLWrapTools.dll
   ```

2. Restart Notepad++

3. Look for "XML Wrap Tools" in the Plugins menu

## For Users

### Available Commands

| Command | Wraps With | Example |
|---------|-----------|---------|
| Wrap as head | `<head>...</head>` | `<head>Chapter 1</head>` |
| Wrap as title | `<title>...</title>` | `<title>My Book</title>` |
| Wrap as hi | `<hi>...</hi>` | `<hi>important</hi>` |
| Wrap as quote | `<quote>...</quote>` | `<quote>citation</quote>` |
| Wrap as trailer | `<trailer>...</trailer>` | `<trailer>end</trailer>` |
| Wrap as foreign | `<foreign xml:lang="en">...</foreign>` | `<foreign xml:lang="en">Hello</foreign>` |
| Wrap with Serbian quotes | `„..."` | `„Добар дан"` |

### How to Use

1. **Select text** in your document
2. **Choose** a wrap command:
   - From menu: Plugins → XML Wrap Tools → [command]
   - From toolbar: Click the appropriate icon
3. **Result:** Selected text is instantly wrapped

### Keyboard Shortcuts

You can assign keyboard shortcuts through Notepad++:
1. Settings → Shortcut Mapper → Plugin commands
2. Find "XML Wrap Tools" commands
3. Double-click to assign shortcut

### Tips

- All operations support **Undo** (Ctrl+Z)
- Works with **Unicode** text (including Cyrillic, emoji, etc.)
- If nothing is selected, you'll get a helpful message
- Use toolbar icons for fastest access
- Commands work on any text editor tab

## Troubleshooting

**Plugin doesn't appear:**
- Verify DLL location: `plugins\XMLWrapTools\XMLWrapTools.dll`
- Restart Notepad++
- Check Windows didn't block the DLL (Properties → Unblock)

**Build fails:**
- Ensure Visual Studio 2022 is installed
- Verify C++ Desktop Development workload is installed
- Select x64 platform (not Win32)

**"No text selected" appears when text is highlighted:**
- Try clicking in the editor first
- Verify text is actually selected (highlighted in blue)

## Support

For issues, questions, or contributions:
- GitHub Issues: https://github.com/sasa5linkar/Notepad-eltec-pluginn/issues
- Pull Requests welcome!

## License

MIT License - See LICENSE file for details

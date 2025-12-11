# Color Value Finder v0.1.2 - Windows Build

**Status:** [Add build status and date here]

## Contents

- `ColorValueFinder.exe` - Windows executable (x86_64)
- `README.md` - Project documentation
- `LICENSE.md` - License
- `CHANGELOG.md` - Release notes

## Installation

1. Extract the zip file
2. Double-click `ColorValueFinder.exe`
3. If you see "Windows protected your PC", click "More info" → "Run anyway"

## Requirements

- Windows 10 or later
- Visual C++ Runtime (automatically installed on most systems)
  - If missing, download from: https://support.microsoft.com/en-us/help/2977003/

## Features

✨ Convert between HEX, RGB, HSV, HSL, and CMYK color formats  
🎨 Interactive color picker wheel  
📋 Copy color values to clipboard  
🖱️ Eyedropper tool - Pick colors from anywhere on screen  
🌈 Real-time color preview with transparency  
🎯 Modern dark-themed interface

## Build Instructions

See `../BUILD_INSTRUCTIONS.md` for detailed Windows build instructions.

## Troubleshooting

**"ColorValueFinder.exe not found"**
- Extract the entire zip file first

**"Visual C++ Runtime Error"**
- Install: https://support.microsoft.com/en-us/help/2977003/

**Application won't start**
- Check if OpenGL is supported on your GPU
- Update graphics drivers
- Try running from Command Prompt to see error messages:
  ```
  ColorValueFinder.exe
  ```

## More Information

- GitHub: https://github.com/mattanmr/color_value_finder
- Report issues: https://github.com/mattanmr/color_value_finder/issues
- License: See LICENSE.md

---

Made with ❤️ for designers and developers

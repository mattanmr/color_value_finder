# Color Value Finder

A sleek, cross-platform GUI application for converting and analyzing color values across multiple formats. Built with C++, Dear ImGui, and GLFW.

**[🔗 Download Latest Release](https://github.com/mattanmr/color_value_finder/releases)** • **[📖 Documentation](#building-from-source)** • **[🐛 Report Issues](https://github.com/mattanmr/color_value_finder/issues)**

## ✨ Features

- 🎨 **Multi-Format Color Converter**: Seamlessly convert between HEX, RGB, HSV, HSL, and CMYK
- 🌈 **Interactive Color Picker**: Visual hue wheel with real-time preview
- 📋 **One-Click Copy**: Copy RGBA and HEX values instantly
- 🖱️ **Eyedropper Tool**: Pick colors directly from your screen (Windows)
- 👁️ **Transparency Support**: Visual checkerboard preview for alpha channel
- 🎯 **Modern UI**: Dark-themed interface with smooth interactions
- ⚡ **Real-time Sync**: Changes in any format instantly update all others
- 🌍 **Cross-Platform**: Windows, macOS, and Linux support

## 📥 Quick Start

### Download Pre-built Binary

Visit the [Releases page](https://github.com/mattanmr/color_value_finder/releases) to download the latest binary for your platform:
- **macOS**: Universal binary (Intel + Apple Silicon)
- **Windows**: x86_64 executable
- **Linux**: x86_64 executable

### Build from Source

**Requirements:**
- CMake 3.15+
- C++17 compatible compiler
- OpenGL 3.3+ support
- Git

**macOS:**
```bash
git clone https://github.com/mattanmr/color_value_finder.git
cd color_value_finder
mkdir build && cd build
cmake -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" ..
cmake --build . --config Release
./bin/ColorValueFinder
```

**Windows:**
```powershell
git clone https://github.com/mattanmr/color_value_finder.git
cd color_value_finder
mkdir build
cd build
cmake ..
cmake --build . --config Release
.\bin\Release\ColorValueFinder.exe
```

**Linux:**
```bash
# Ubuntu/Debian dependencies:
sudo apt-get install build-essential cmake libgl1-mesa-dev xorg-dev

# Build:
git clone https://github.com/mattanmr/color_value_finder.git
cd color_value_finder
mkdir build && cd build
cmake ..
cmake --build . --config Release
./bin/ColorValueFinder
```

## 🎮 Usage

1. **Enter a color** using any method:
   - Type HEX codes: `#FF5733` or `#FF5733FF` (with alpha)
   - Adjust RGB, HSV, HSL, or CMYK sliders
   - Click the interactive color picker wheel
   - Use the eyedropper (Windows only) to sample from screen

2. **View instant conversions** across all formats

3. **Copy values** with one click:
   - `Copy RGBA`: Paste as `rgba(255, 87, 51, 1.0)`
   - `Copy HEX`: Paste as `#FF5733FF`

## 📋 Supported Color Formats

## 📋 Supported Color Formats

| Format | Range | Example |
|--------|-------|---------|
| **HEX** | #RRGGBB or #RRGGBBAA | #FF5733FF |
| **RGB** | 0-255 per channel + alpha 0-1 | rgb(255, 87, 51, 1.0) |
| **HSV** | H: 0-360°, S/V: 0-1 | hsv(9°, 0.80, 1.00) |
| **HSL** | H: 0-360°, S/L: 0-1 | hsl(9°, 1.00, 0.60) |
| **CMYK** | 0-1 per channel | cmyk(0.00, 0.66, 0.80, 0.00) |

## 📋 Project Structure

```
color_value_finder/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── CHANGELOG.md                # Version history
├── LICENSE.md                  # License (MIT)
├── releases/                   # Release packages
│   └── v0.1.2/
│       ├── mac/               # macOS binary
│       ├── win/               # Windows binary (placeholder)
│       └── linux/             # Linux binary (placeholder)
├── external/
│   ├── glfw/                  # GLFW window/input handling
│   └── imgui/                 # Dear ImGui GUI framework
└── src/
    ├── main.cpp               # Application entry point
    ├── ColorConverter.h/.cpp  # Color format conversions
    └── PlatformUtils.h/.cpp   # Platform-specific utilities
```

## 🔧 Technologies

- **[Dear ImGui](https://github.com/ocornut/imgui)**: Immediate-mode GUI framework
- **[GLFW](https://www.glfw.org/)**: Window and input management
- **OpenGL 3.3+**: Graphics rendering
- **CMake**: Build system

## 📦 Requirements

### All Platforms
- CMake 3.15 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2019+)
- Git (for cloning)

### Windows
- Visual Studio 2019+ or MinGW-w64
- OpenGL support from GPU driver

### macOS
- Xcode Command Line Tools: `xcode-select --install`
- macOS 10.13+

### Linux
**Ubuntu/Debian:**
```bash
sudo apt-get install build-essential cmake libgl1-mesa-dev xorg-dev
```

**Fedora:**
```bash
sudo dnf install gcc-c++ cmake mesa-libGL-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel
```

**Arch:**
```bash
sudo pacman -S base-devel cmake mesa libxrandr libxinerama libxcursor libxi
```

## 🏗️ Building from Source

Detailed build instructions for each platform are available in `releases/v0.1.2/BUILD_INSTRUCTIONS.md`.

### Quick Build (All Platforms)

```bash
git clone https://github.com/mattanmr/color_value_finder.git
cd color_value_finder
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

Output binary: `./bin/ColorValueFinder` (or `.exe` on Windows)

## 🚀 Platform-Specific Notes

### Windows
- Eyedropper tool fully functional
- Can run from Command Prompt: `ColorValueFinder.exe`
- Requires Visual C++ Runtime (usually pre-installed)

### macOS
- Universal binary supports both Intel and Apple Silicon
- To run: `chmod +x ColorValueFinder && ./ColorValueFinder`
- Gatekeeper may prompt on first run; click "Open"
- Eyedropper not yet implemented (contributions welcome!)

### Linux
- Requires X11 or Wayland compositor
- Run: `chmod +x ColorValueFinder && ./ColorValueFinder`
- Eyedropper not yet implemented (contributions welcome!)

## ❓ Troubleshooting

**"Cannot open" / "Unknown developer" (macOS)**
```bash
xattr -d com.apple.quarantine ColorValueFinder
```

**OpenGL error / Window won't appear**
- Update graphics drivers
- Verify OpenGL 3.3+ support: `glxinfo | grep "OpenGL version"` (Linux)
- On VMs, enable 3D acceleration in VM settings

**Build fails: CMake not found**
- Install CMake: https://cmake.org/download/
- Or via package manager: `brew install cmake` (macOS), `apt install cmake` (Linux)

**Build fails: C++17 compiler not found**
- macOS: Update Xcode: `xcode-select --install`
- Linux: `sudo apt install g++` (Ubuntu) or `sudo dnf install gcc-c++` (Fedora)
- Windows: Install Visual Studio 2019 or later

## 📝 License

This project is licensed under the MIT License - see [LICENSE.md](LICENSE.md) for details.

## 🤝 Contributing

Contributions are welcome! Please feel free to:
- [Report bugs](https://github.com/mattanmr/color_value_finder/issues)
- [Suggest features](https://github.com/mattanmr/color_value_finder/issues)
- Submit pull requests

### Known Limitations & Future Work
- Eyedropper tool: macOS/Linux implementations needed
- CMYK conversion: Some edge cases need refinement
- Planned: Color history, favorites, palettes, gradient editor

## 💝 Credits

Created with ❤️ for designers, developers, and color enthusiasts.

---

**[Download Now](https://github.com/mattanmr/color_value_finder/releases)** • **[Report Issue](https://github.com/mattanmr/color_value_finder/issues)** • **[View Changelog](CHANGELOG.md)**

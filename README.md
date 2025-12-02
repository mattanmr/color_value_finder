# Color Value Finder

A cross-platform GUI application for finding and converting color values between different color formats. Built with C++, Dear ImGui, and GLFW.

![Color Value Finder](screenshot.png)

## Features

- **Visual Color Preview**: See your selected color in real-time
- **Multiple Input Methods**:
  - HEX color codes (#RRGGBB)
  - RGB sliders (0-255)
  - HSV sliders (Hue: 0-360°, Saturation & Value: 0-1)
  - HSL sliders (Hue: 0-360°, Saturation & Lightness: 0-1)
  - CMYK sliders (0-1)
  - Interactive color picker with hue wheel
- **Real-time Conversion**: Changes in one format automatically update all others
- **Cross-Platform**: Runs on Windows, macOS, and Linux

## Requirements

### All Platforms
- CMake 3.15 or higher
- C++17 compatible compiler
- Git (for cloning dependencies)

### Platform-Specific Requirements

#### Windows
- Visual Studio 2019 or later (with C++ development tools)
- OR MinGW-w64

#### macOS
- Xcode Command Line Tools
- Install with: `xcode-select --install`

#### Linux
- GCC 7+ or Clang 5+
- OpenGL development libraries
- GLFW dependencies

```bash
# Ubuntu/Debian
sudo apt-get install build-essential cmake libgl1-mesa-dev xorg-dev

# Fedora
sudo dnf install gcc-c++ cmake mesa-libGL-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel

# Arch Linux
sudo pacman -S base-devel cmake mesa libxrandr libxinerama libxcursor libxi
```

## Building from Source

### Windows

#### Using Visual Studio

```powershell
# Clone the repository
git clone <repository-url>
cd color_value_finder

# Create build directory
mkdir build
cd build

# Generate Visual Studio solution
cmake ..

# Build the project
cmake --build . --config Release

# Run the application
.\bin\Release\ColorValueFinder.exe
```

#### Using MinGW

```powershell
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Release
.\bin\ColorValueFinder.exe
```

### macOS

```bash
# Clone the repository
git clone <repository-url>
cd color_value_finder

# Create build directory
mkdir build
cd build

# Generate makefiles
cmake ..

# Build the project
cmake --build . --config Release

# Run the application
./bin/ColorValueFinder
```

### Linux

```bash
# Clone the repository
git clone <repository-url>
cd color_value_finder

# Create build directory
mkdir build
cd build

# Generate makefiles
cmake ..

# Build the project
cmake --build . --config Release

# Run the application
./bin/ColorValueFinder
```

## Usage

1. **Launch the Application**: Run the executable built in the previous step
2. **Select a Color**: Use any of the following methods:
   - Type a HEX code (e.g., `#FF5733`)
   - Adjust RGB sliders
   - Adjust HSV sliders
   - Adjust HSL sliders
   - Adjust CMYK sliders
   - Use the interactive color picker wheel
3. **View Conversions**: All color format values update automatically

## Project Structure

```
color_value_finder/
├── CMakeLists.txt          # Main CMake configuration
├── README.md               # This file
├── .gitignore             # Git ignore rules
├── external/              # External dependencies
│   ├── glfw/             # GLFW (window/input handling)
│   └── imgui/            # Dear ImGui (GUI framework)
└── src/                   # Source code
    ├── main.cpp          # Application entry point and GUI
    ├── ColorConverter.h   # Color conversion header
    └── ColorConverter.cpp # Color conversion implementation
```

## Technologies Used

- **[Dear ImGui](https://github.com/ocornut/imgui)**: Immediate mode GUI framework
- **[GLFW](https://www.glfw.org/)**: Cross-platform window and input handling
- **OpenGL 3.3**: Graphics rendering
- **CMake**: Cross-platform build system

## Color Conversion Details

The application supports conversions between:
- **HEX**: Hexadecimal color codes (#RRGGBB)
- **RGB**: Red, Green, Blue (0-255)
- **HSV**: Hue (0-360°), Saturation (0-1), Value (0-1)
- **HSL**: Hue (0-360°), Saturation (0-1), Lightness (0-1)
- **CMYK**: Cyan, Magenta, Yellow, Key/Black (0-1)

All conversions are performed in real-time with high precision.

## License

This project is open source and available for educational and commercial use.

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests.

## Troubleshooting

### Build Errors

**CMake cannot find OpenGL**:
- Windows: Ensure you have a GPU driver installed
- Linux: Install mesa development packages
- macOS: OpenGL should be available by default

**GLFW download fails**:
- Check your internet connection
- Try running cmake again (it will resume the download)

**Compilation errors**:
- Ensure you have a C++17 compatible compiler
- Update CMake to version 3.15 or higher

### Runtime Errors

**Application crashes on startup**:
- Update your graphics drivers
- Verify OpenGL 3.3 support on your system

**Window doesn't appear**:
- Check if the application is running in the background
- Try running from the command line to see error messages

## Author

Created with ❤️ for color enthusiasts and developers

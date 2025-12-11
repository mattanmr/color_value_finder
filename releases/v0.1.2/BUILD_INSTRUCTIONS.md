# Color Value Finder v0.1.2 - Build Instructions

This directory contains organized release folders for different platforms. Follow the platform-specific instructions below to build and package for your system.

## Directory Structure

```
releases/v0.1.2/
├── mac/          # macOS builds (Intel x86_64 + Apple Silicon arm64)
├── win/          # Windows builds (x86_64)
├── linux/        # Linux builds (x86_64)
├── CHANGELOG.md  # Release notes
├── LICENSE.md    # License
├── README.md     # Project documentation
└── BUILD_INSTRUCTIONS.md  # This file
```

---

## macOS Build

**Requirements:**
- macOS 10.13+
- Xcode Command Line Tools: `xcode-select --install`
- CMake 3.15+
- Git

**Build & Package:**

```bash
cd /path/to/color_value_finder
mkdir -p build && cd build

# Build universal binary (Intel + Apple Silicon)
cmake -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" ..
cmake --build . --config Release

# Copy to release folder
cp bin/ColorValueFinder ../releases/v0.1.2/mac/
cd ../releases/v0.1.2/mac

# Create zip package
zip -r ../ColorValueFinder-v0.1.2-macOS.zip .
```

**Installation for Users:**
```bash
chmod +x ColorValueFinder
xattr -d com.apple.quarantine ColorValueFinder
./ColorValueFinder
```

---

## Windows Build

**Requirements:**
- Windows 10/11
- Visual Studio 2019+ (or Visual Studio Build Tools)
- CMake 3.15+
- Git

**Build & Package:**

```bash
cd C:\path\to\color_value_finder
mkdir build && cd build

# Generate Visual Studio solution
cmake -G "Visual Studio 17 2022" ..

# Build Release
cmake --build . --config Release

# Copy to release folder
xcopy bin\Release\ColorValueFinder.exe ..\releases\v0.1.2\win\
copy ..\README.md ..\releases\v0.1.2\win\
copy ..\LICENSE.md ..\releases\v0.1.2\win\
copy ..\CHANGELOG.md ..\releases\v0.1.2\win\

# Create zip package (using 7-Zip or Windows built-in)
cd ..\releases\v0.1.2
powershell -Command "Compress-Archive -Path win -DestinationPath ColorValueFinder-v0.1.2-Windows.zip"
```

**Installation for Users:**
- Extract zip file
- Double-click `ColorValueFinder.exe` to run
- (Optional) Add to PATH for command-line use

**Note:** Requires Visual C++ Runtime. Users can download from Microsoft if needed.

---

## Linux Build

**Requirements:**
- GCC 7+ or Clang 5+
- CMake 3.15+
- OpenGL development libraries
- Git

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libgl1-mesa-dev xorg-dev
```

**Fedora:**
```bash
sudo dnf install gcc-c++ cmake mesa-libGL-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel cmake mesa libxrandr libxinerama libxcursor libxi
```

**Build & Package:**

```bash
cd /path/to/color_value_finder
mkdir -p build && cd build

# Build
cmake ..
cmake --build . --config Release

# Copy to release folder
cp bin/ColorValueFinder ../releases/v0.1.2/linux/
cp ../README.md ../releases/v0.1.2/linux/
cp ../LICENSE.md ../releases/v0.1.2/linux/
cp ../CHANGELOG.md ../releases/v0.1.2/linux/

# Create tar.gz package
cd ../releases/v0.1.2
tar -czf ColorValueFinder-v0.1.2-Linux.tar.gz linux/
```

**Installation for Users:**
```bash
tar -xzf ColorValueFinder-v0.1.2-Linux.tar.gz
cd linux
chmod +x ColorValueFinder
./ColorValueFinder
```

---

## Creating Multi-Platform Release Package

After building for all platforms:

```bash
cd releases/v0.1.2

# Create archive with all platforms
zip -r ColorValueFinder-v0.1.2-All-Platforms.zip \
  mac/ColorValueFinder \
  mac/README.md \
  mac/LICENSE.md \
  mac/CHANGELOG.md \
  win/ColorValueFinder.exe \
  win/README.md \
  win/LICENSE.md \
  win/CHANGELOG.md \
  linux/ColorValueFinder \
  linux/README.md \
  linux/LICENSE.md \
  linux/CHANGELOG.md
```

---

## Release Checklist

- [ ] Build macOS binary (universal)
- [ ] Build Windows executable
- [ ] Build Linux executable
- [ ] Test each binary on target platform
- [ ] Create platform-specific zip/tar archives
- [ ] Update version numbers in CMakeLists.txt if needed
- [ ] Create/update CHANGELOG.md
- [ ] Push changes to GitHub
- [ ] Create GitHub Release with all platform packages as assets
- [ ] Tag release with version: `git tag -a v0.1.2 -m "Release v0.1.2"`

---

## Troubleshooting

**macOS: "Cannot be opened because it is from an unidentified developer"**
```bash
xattr -d com.apple.quarantine ColorValueFinder
```

**Windows: "Missing Visual C++ Runtime"**
- Direct users to: https://support.microsoft.com/en-us/help/2977003/

**Linux: "libGL.so.1 not found"**
```bash
sudo apt-get install libgl1-mesa-glx
```

---

## Future Releases

For v0.1.3, v0.2.0, etc., simply:
1. Create new folder: `releases/vX.Y.Z/`
2. Create subdirectories: `mac/`, `win/`, `linux/`
3. Follow the same build process above
4. Update CHANGELOG.md and version in CMakeLists.txt
5. Repeat from "Creating Multi-Platform Release Package"

This maintains a consistent, organized structure for all releases.

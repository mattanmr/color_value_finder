# Color Value Finder v0.1.2 - Linux Build

**Status:** [Add build status and date here]

## Contents

- `ColorValueFinder` - Linux executable (x86_64)
- `README.md` - Project documentation
- `LICENSE.md` - License
- `CHANGELOG.md` - Release notes

## Installation

```bash
# Extract
tar -xzf ColorValueFinder-v0.1.2-Linux.tar.gz
cd linux

# Make executable
chmod +x ColorValueFinder

# Run
./ColorValueFinder
```

## Requirements

- Linux (x86_64)
- OpenGL 3.3+ support
- GTK 3 (for file dialogs, if used)

**Dependencies by Distribution:**

**Ubuntu/Debian:**
```bash
sudo apt-get install libgl1-mesa-glx libxrandr2 libxinerama1 libxcursor1 libxi6
```

**Fedora:**
```bash
sudo dnf install mesa-libGL libXrandr libXinerama libXcursor libXi
```

**Arch Linux:**
```bash
sudo pacman -S mesa libxrandr libxinerama libxcursor libxi
```

## Features

✨ Convert between HEX, RGB, HSV, HSL, and CMYK color formats  
🎨 Interactive color picker wheel  
📋 Copy color values to clipboard  
🌈 Real-time color preview with transparency  
🎯 Modern dark-themed interface

## Build Instructions

See `../BUILD_INSTRUCTIONS.md` for detailed Linux build instructions.

## Troubleshooting

**"libGL.so.1 not found"**
```bash
sudo apt-get install libgl1-mesa-glx
```

**"libX11.so.6 not found"**
```bash
sudo apt-get install libx11-6
```

**Application crashes on startup**
- Ensure your GPU supports OpenGL 3.3+
- Try: `glxinfo | grep "OpenGL version"`
- Update graphics drivers

**Permission denied when running**
```bash
chmod +x ColorValueFinder
```

## More Information

- GitHub: https://github.com/mattanmr/color_value_finder
- Report issues: https://github.com/mattanmr/color_value_finder/issues
- License: See LICENSE.md

---

Made with ❤️ for designers and developers

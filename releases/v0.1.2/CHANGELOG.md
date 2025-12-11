# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.2] - 2025-12-11

### Added
- Initial public release
- Multi-format color picker with support for HEX, RGB, HSV, HSL, and CMYK
- Interactive color picker wheel with hue wheel visualization
- Real-time color format conversion and synchronization
- Copy-to-clipboard functionality for RGBA and HEX values
- Eyedropper tool for picking colors from screen (Windows)
- Visual color preview with transparency checkerboard
- Modern dark-themed UI with customized ImGui styling
- Cross-platform support for Windows, macOS, and Linux
- Comprehensive color conversion algorithms
- Responsive two-column layout for intuitive user interaction

### Known Issues
- Eyedropper tool currently only available on Windows (macOS/Linux support to be added)
- Some edge cases in CMYK conversion may need refinement

## [Unreleased]

### Planned Features
- macOS eyedropper implementation using Quartz
- Linux eyedropper implementation
- Color history and favorites
- Custom color palettes
- RGB/HSV gradient editor
- Accessibility improvements (keyboard shortcuts, screen reader support)
- Improved CMYK conversion precision

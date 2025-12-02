#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H

#include <string>
#include <array>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

struct RGB {
    float r, g, b; // 0.0 to 1.0
    RGB(float r = 0.0f, float g = 0.0f, float b = 0.0f) : r(r), g(g), b(b) {}
};

struct HSV {
    float h, s, v; // h: 0-360, s: 0-1, v: 0-1
    HSV(float h = 0.0f, float s = 0.0f, float v = 0.0f) : h(h), s(s), v(v) {}
};

struct HSL {
    float h, s, l; // h: 0-360, s: 0-1, l: 0-1
    HSL(float h = 0.0f, float s = 0.0f, float l = 0.0f) : h(h), s(s), l(l) {}
};

struct CMYK {
    float c, m, y, k; // 0.0 to 1.0
    CMYK(float c = 0.0f, float m = 0.0f, float y = 0.0f, float k = 0.0f) : c(c), m(m), y(y), k(k) {}
};

class ColorConverter {
public:
    // RGB conversions
    static std::string RGBToHex(const RGB& rgb);
    static RGB HexToRGB(const std::string& hex);
    
    static HSV RGBToHSV(const RGB& rgb);
    static RGB HSVToRGB(const HSV& hsv);
    
    static HSL RGBToHSL(const RGB& rgb);
    static RGB HSLToRGB(const HSL& hsl);
    
    static CMYK RGBToCMYK(const RGB& rgb);
    static RGB CMYKToRGB(const CMYK& cmyk);
    
    // Helper functions
    static float Clamp(float value, float min = 0.0f, float max = 1.0f);
    static int HexCharToInt(char c);
    static char IntToHexChar(int value);
};

#endif // COLOR_CONVERTER_H

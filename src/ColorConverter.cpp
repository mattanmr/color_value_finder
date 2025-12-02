#include "ColorConverter.h"

// RGB to HEX
std::string ColorConverter::RGBToHex(const RGB& rgb) {
    int r = static_cast<int>(Clamp(rgb.r) * 255);
    int g = static_cast<int>(Clamp(rgb.g) * 255);
    int b = static_cast<int>(Clamp(rgb.b) * 255);
    
    std::stringstream ss;
    ss << "#" 
       << std::hex << std::setfill('0') << std::setw(2) << r
       << std::hex << std::setfill('0') << std::setw(2) << g
       << std::hex << std::setfill('0') << std::setw(2) << b;
    
    std::string result = ss.str();
    // Convert to uppercase
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// HEX to RGB
RGB ColorConverter::HexToRGB(const std::string& hex) {
    std::string cleanHex = hex;
    if (cleanHex[0] == '#') {
        cleanHex = cleanHex.substr(1);
    }
    
    if (cleanHex.length() != 6) {
        return RGB(0, 0, 0);
    }
    
    int r = HexCharToInt(cleanHex[0]) * 16 + HexCharToInt(cleanHex[1]);
    int g = HexCharToInt(cleanHex[2]) * 16 + HexCharToInt(cleanHex[3]);
    int b = HexCharToInt(cleanHex[4]) * 16 + HexCharToInt(cleanHex[5]);
    
    return RGB(r / 255.0f, g / 255.0f, b / 255.0f);
}

// RGB to HSV
HSV ColorConverter::RGBToHSV(const RGB& rgb) {
    float r = Clamp(rgb.r);
    float g = Clamp(rgb.g);
    float b = Clamp(rgb.b);
    
    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float delta = max - min;
    
    HSV hsv;
    hsv.v = max;
    
    if (max == 0.0f) {
        hsv.s = 0.0f;
        hsv.h = 0.0f;
        return hsv;
    }
    
    hsv.s = delta / max;
    
    if (delta == 0.0f) {
        hsv.h = 0.0f;
    } else if (max == r) {
        hsv.h = 60.0f * fmod(((g - b) / delta), 6.0f);
    } else if (max == g) {
        hsv.h = 60.0f * (((b - r) / delta) + 2.0f);
    } else {
        hsv.h = 60.0f * (((r - g) / delta) + 4.0f);
    }
    
    if (hsv.h < 0.0f) {
        hsv.h += 360.0f;
    }
    
    return hsv;
}

// HSV to RGB
RGB ColorConverter::HSVToRGB(const HSV& hsv) {
    float h = fmod(hsv.h, 360.0f);
    if (h < 0.0f) h += 360.0f;
    
    float s = Clamp(hsv.s);
    float v = Clamp(hsv.v);
    
    float c = v * s;
    float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;
    
    float r = 0, g = 0, b = 0;
    
    if (h >= 0 && h < 60) {
        r = c; g = x; b = 0;
    } else if (h >= 60 && h < 120) {
        r = x; g = c; b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0; g = c; b = x;
    } else if (h >= 180 && h < 240) {
        r = 0; g = x; b = c;
    } else if (h >= 240 && h < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }
    
    return RGB(r + m, g + m, b + m);
}

// RGB to HSL
HSL ColorConverter::RGBToHSL(const RGB& rgb) {
    float r = Clamp(rgb.r);
    float g = Clamp(rgb.g);
    float b = Clamp(rgb.b);
    
    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float delta = max - min;
    
    HSL hsl;
    hsl.l = (max + min) / 2.0f;
    
    if (delta == 0.0f) {
        hsl.h = 0.0f;
        hsl.s = 0.0f;
        return hsl;
    }
    
    hsl.s = delta / (1.0f - fabs(2.0f * hsl.l - 1.0f));
    
    if (max == r) {
        hsl.h = 60.0f * fmod(((g - b) / delta), 6.0f);
    } else if (max == g) {
        hsl.h = 60.0f * (((b - r) / delta) + 2.0f);
    } else {
        hsl.h = 60.0f * (((r - g) / delta) + 4.0f);
    }
    
    if (hsl.h < 0.0f) {
        hsl.h += 360.0f;
    }
    
    return hsl;
}

// HSL to RGB
RGB ColorConverter::HSLToRGB(const HSL& hsl) {
    float h = fmod(hsl.h, 360.0f);
    if (h < 0.0f) h += 360.0f;
    
    float s = Clamp(hsl.s);
    float l = Clamp(hsl.l);
    
    float c = (1.0f - fabs(2.0f * l - 1.0f)) * s;
    float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
    float m = l - c / 2.0f;
    
    float r = 0, g = 0, b = 0;
    
    if (h >= 0 && h < 60) {
        r = c; g = x; b = 0;
    } else if (h >= 60 && h < 120) {
        r = x; g = c; b = 0;
    } else if (h >= 120 && h < 180) {
        r = 0; g = c; b = x;
    } else if (h >= 180 && h < 240) {
        r = 0; g = x; b = c;
    } else if (h >= 240 && h < 300) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }
    
    return RGB(r + m, g + m, b + m);
}

// RGB to CMYK
CMYK ColorConverter::RGBToCMYK(const RGB& rgb) {
    float r = Clamp(rgb.r);
    float g = Clamp(rgb.g);
    float b = Clamp(rgb.b);
    
    CMYK cmyk;
    cmyk.k = 1.0f - std::max({r, g, b});
    
    if (cmyk.k == 1.0f) {
        cmyk.c = 0.0f;
        cmyk.m = 0.0f;
        cmyk.y = 0.0f;
        return cmyk;
    }
    
    cmyk.c = (1.0f - r - cmyk.k) / (1.0f - cmyk.k);
    cmyk.m = (1.0f - g - cmyk.k) / (1.0f - cmyk.k);
    cmyk.y = (1.0f - b - cmyk.k) / (1.0f - cmyk.k);
    
    return cmyk;
}

// CMYK to RGB
RGB ColorConverter::CMYKToRGB(const CMYK& cmyk) {
    float c = Clamp(cmyk.c);
    float m = Clamp(cmyk.m);
    float y = Clamp(cmyk.y);
    float k = Clamp(cmyk.k);
    
    float r = (1.0f - c) * (1.0f - k);
    float g = (1.0f - m) * (1.0f - k);
    float b = (1.0f - y) * (1.0f - k);
    
    return RGB(r, g, b);
}

// Helper: Clamp value
float ColorConverter::Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Helper: Hex char to int
int ColorConverter::HexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

// Helper: Int to hex char
char ColorConverter::IntToHexChar(int value) {
    if (value >= 0 && value <= 9) return '0' + value;
    if (value >= 10 && value <= 15) return 'A' + (value - 10);
    return '0';
}

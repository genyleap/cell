#if __has_include("color.hpp")
#   include "color.hpp"
#else
#   error "Cell's "color.hpp" was not found!"
#endif

#if __has_include("core/core.hpp")
#   include "core/core.hpp"
#else
#   error "Cell's "core/core.hpp" was not found!"
#endif

CELL_USING_NAMESPACE Cell;
CELL_USING_NAMESPACE Cell::System;
CELL_USING_NAMESPACE Cell::Utility;
CELL_USING_NAMESPACE Cell::Types;
CELL_USING_NAMESPACE Cell::JSon;

CELL_NAMESPACE_BEGIN(Cell::Convertors::Color)

std::string ColorConverter::rgbToHex(int red, int green, int blue)
{
    std::stringstream ss;
    ss << "#" << std::hex << ((red << 16) | (green << 8) | blue);
    return ss.str();
}

void ColorConverter::hexToRgb(const std::string& hex, int& red, int& green, int& blue)
{
    std::stringstream ss;
    ss << std::hex << hex.substr(1); // Exclude the '#' character
    ss >> red >> green >> blue;
}

void ColorConverter::rgbToCmyk(int red, int green, int blue, double& cyan, double& magenta, double& yellow, double& black)
{
    double r = red / 255.0;
    double g = green / 255.0;
    double b = blue / 255.0;

    black = std::min(1.0 - r, std::min(1.0 - g, 1.0 - b));
    cyan = (1.0 - r - black) / (1.0 - black);
    magenta = (1.0 - g - black) / (1.0 - black);
    yellow = (1.0 - b - black) / (1.0 - black);
}

void ColorConverter::cmykToRgb(double cyan, double magenta, double yellow, double black, int& red, int& green, int& blue)
{
    red = static_cast<int>((1.0 - cyan) * (1.0 - black) * 255.0);
    green = static_cast<int>((1.0 - magenta) * (1.0 - black) * 255.0);
    blue = static_cast<int>((1.0 - yellow) * (1.0 - black) * 255.0);
}

void ColorConverter::rgbToHsl(int red, int green, int blue, double& hue, double& saturation, double& lightness)
{
    double r = red / 255.0;
    double g = green / 255.0;
    double b = blue / 255.0;

    double maxColor = std::max(r, std::max(g, b));
    double minColor = std::min(r, std::min(g, b));

    lightness = (maxColor + minColor) / 2.0;

    if (maxColor == minColor) {
        hue = saturation = 0.0; // Monochromatic
    } else {
        double delta = maxColor - minColor;
        saturation = lightness > 0.5 ? delta / (2.0 - maxColor - minColor) : delta / (maxColor + minColor);

        if (maxColor == r) {
            hue = (g - b) / delta + (g < b ? 6.0 : 0.0);
        } else if (maxColor == g) {
            hue = (b - r) / delta + 2.0;
        } else {
            hue = (r - g) / delta + 4.0;
        }

        hue /= 6.0;
    }
}

void ColorConverter::hslToRgb(double hue, double saturation, double lightness, int& red, int& green, int& blue)
{
    if (saturation == 0.0) {
        red = green = blue = static_cast<int>(lightness * 255.0);
    } else {
        auto hueToRgb = [](double p, double q, double t) {
            if (t < 0.0) t += 1.0;
            if (t > 1.0) t -= 1.0;
            if (t < 1.0 / 6.0) return p + (q - p) * 6.0 * t;
            if (t < 1.0 / 2.0) return q;
            if (t < 2.0 / 3.0) return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
            return p;
        };

        double q = lightness < 0.5 ? lightness * (1.0 + saturation) : lightness + saturation - lightness * saturation;
        double p = 2.0 * lightness - q;

        red = static_cast<int>(hueToRgb(p, q, hue + 1.0 / 3.0) * 255.0);
        green = static_cast<int>(hueToRgb(p, q, hue) * 255.0);
        blue = static_cast<int>(hueToRgb(p, q, hue - 1.0 / 3.0) * 255.0);
    }
}

CELL_NAMESPACE_END


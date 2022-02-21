#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct map {
    std::vector<unsigned char> map;
    int width;
    int height;
};

/**
 * m = map object
 * diameter = diameter of circle to draw
 * x = x coordinate of circle
 * y = y coordinate of circle
 * */
void drawCircle(map &m, int diameter, int x, int y, int weight) {
    int radius = diameter / 2;
    int lx = x - radius;

    // y = sqrt(r^2 - x^2)
    for (int i = 0; i < diameter; i++) {
        int xi = lx + i;
        int ty = std::round(std::sqrt(std::pow(radius, 2) - std::pow(i - radius, 2)));
        for (int w = -weight + 1; w < weight; w++) {
            m.map[xi + (y + ty + w) * m.width] = 0xFF;
            m.map[xi + (y - ty - w) * m.width] = 0xFF;
            m.map[(x + ty + w) + xi * m.width] = 0xFF;
            m.map[(x - ty - w) + xi * m.width] = 0xFF;

            // m.map[xi + (y + ty - w) * m.width] = 0xFF;
            // m.map[xi + (y - ty + w) * m.width] = 0xFF;
            // m.map[(x + ty - w) + xi * m.width] = 0xFF;
            // m.map[(x - ty + w) + xi * m.width] = 0xFF;
        }
    }
}

map drawHoopSkirt(int waist, int height, int thickness = 1) {
    // Pixel perfect drawing will be fucked by odd numbers
    waist -= waist % 2;
    height -= height % 2;

    int w = waist + height * 2;
    map m;
    m.width = w;
    m.height = w;
    m.map.resize(w * w, 0);
    
    // drawCircle(m, waist, w / 2 - waist / 2, w / 2, w / 2);
    // drawCircle(m, waist + height * 2, 0, w / 2, w / 2);

    drawCircle(m, waist, w / 2, w / 2, 2);
    drawCircle(m, waist + height * 2 - 2 * 2, w / 2, w / 2, 2);

    return m;
}


int main() {
    map m = drawHoopSkirt(100, 300, 1);

    stbi_write_bmp("test.bmp", m.width, m.height, 1, (const void *)m.map.data());

    return 0;
}



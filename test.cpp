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
void drawCircle(map &m, int diameter, int x, int y) {
    int radius = diameter / 2;
    int lx = x - radius;

    // y = sqrt(r^2 - x^2)
    for (int i = 0; i < diameter; i++) {
        int xi = lx + i;
        int ty = std::round(std::sqrt(std::pow(radius, 2) - std::pow(i - radius, 2)));
        m.map[xi + (y + ty) * m.width] = 0xFF;
        m.map[xi + (y - ty) * m.width] = 0xFF;
        m.map[(x + ty) + xi * m.width] = 0xFF;
        m.map[(x - ty) + xi * m.width] = 0xFF;
    }
}

void drawCircleWeight(map &m, int diameter, int x, int y, int weight) {
    drawCircle(m, diameter, x, y);

    weight--;

    for (int i = 1; i <= weight; i++) {
        drawCircle(m, diameter - i * 2, x, y);
        drawCircle(m, diameter + i * 2, x, y);
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

    drawCircleWeight(m, waist, w / 2, w / 2, 2);
    drawCircleWeight(m, waist + height * 2 - 2 * 2, w / 2, w / 2, 2);

    return m;
}


int main() {
    map m = drawHoopSkirt(100, 300, 1);

    m.map[0] = 100;
    m.map[0] = 100;
    m.map[2] = 100;
    m.map[3] = 100;
    stbi_write_bmp("test.bmp", m.width, m.height, 1, (const void *)m.map.data());

    return 0;
}



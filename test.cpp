#include <iostream>
#include <vector>
#include <array>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct map {
    std::vector<unsigned char> map;
    int width;
    int height;
};

void drawCircle(map &m, int diameter, int x, int ax, int ay) {
    int radius = diameter / 2;

    // y = sqrt(r^2 - x^2)
    for (int i = 0; i < diameter; i++) {
        int xi = x + i;
        int y = std::sqrt(std::pow(radius, 2) - std::pow(i - radius, 2));
        m.map[xi + (ax + y) * m.width] = 0xFF;
        m.map[xi + (ax - y) * m.width] = 0xFF;
        m.map[(ay + y) + xi * m.width] = 0xFF;
        m.map[(ay - y) + xi * m.width] = 0xFF;
    }
}

map drawHoopSkirt(int waist, int height, int thickness = 1) {
    waist -= waist % 2;
    height -= height % 2;

    int w = waist + height * 2;
    map m;
    m.width = w;
    m.height = w;
    m.map.resize(w * w, 0);
    
    drawCircle(m, waist, w / 2 - waist / 2, w / 2, w / 2);
    drawCircle(m, waist + height * 2, 0, w / 2, w / 2);

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



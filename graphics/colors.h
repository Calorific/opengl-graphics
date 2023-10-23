#pragma once

// структура для цвета в формате RGB
typedef struct RgbColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

// структура для цвета в формате HSV
typedef struct HsvColor {
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

// функция конвертации из HSV в RGB
RgbColor HsvToRgb(HsvColor hsv);
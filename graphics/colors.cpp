#include "colors.h"

RgbColor HsvToRgb(HsvColor const hsv) {
    RgbColor rgb;

    if (hsv.s == 0) {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }
    
	// определяем в какой сектор попадает Hue
    unsigned char const region = hsv.h / 43;
    unsigned char const remainder = (hsv.h - (region * 43)) * 6; 
    
	// считаем соответствующие значения для формата RGB
    unsigned char const p = hsv.v * (255 - hsv.s) >> 8;
    unsigned char const q = hsv.v * (255 - (hsv.s * remainder >> 8)) >> 8;
    unsigned char const t = hsv.v * (255 - (hsv.s * (255 - remainder) >> 8)) >> 8;
    
	// в зависимости от региона присваиваем значения
    switch (region) {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }
    
    return rgb;
}
#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <complex>
#include <iostream>
#include "glut.h"
#include "colors.h"

using namespace std;

typedef std::complex<double> Complex;
 
Complex sqr(const Complex &v) {
    return pow(v, 2);
}

void resize(int width, int height) {
    
}

void display() {
    glColor3d(0, 0, 0);
    glPointSize(1);
    glBegin(GL_POINTS);
        for (int y = 0; y < 800; y++) {
            for (int x = 0; x < 1200; x++) {
                Complex z(0, 0);
                int i = 0;
                for (; i < 80 && abs(z) < 2; i++)
                    z = sqr(z) + Complex((x - 600.0) / 280, (y - 400.0) / 280);
                
                if (abs(z) >= 2) {
                    HsvColor const hsv{ static_cast<unsigned char>(255 * i / 80), 255, 255 };
                    RgbColor const rgb = HsvToRgb(hsv);
                    glColor3d(rgb.r,rgb.g,rgb.b);
                    glVertex2d(x, y);
                } else {
                    glColor3d(0, 0, 0);
                    glVertex2d(x, y);
                }
            }
        }
    glEnd();
    glFlush();
}

void init() {
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1200.0, 0, 800.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(250, 100);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Mandelbrot Set");
    glutReshapeFunc(resize);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

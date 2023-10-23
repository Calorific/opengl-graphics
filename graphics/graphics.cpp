#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <complex>
#include <iostream>
#include "glut.h"
#include "colors.h"

using namespace std;

#define HEIGHT 800.0 // высота окна
#define WIDTH 1200.0 // ширина окна
#define C_DIVISOR 280.0 // делитель для прибавляемой константы
int ITER_COUNT = 80; // количество итераций для проверки на вхождение точки в множество

typedef std::complex<double> Complex;

void resize(int w, int h) {
    
}

void display() {
    glColor3d(0, 0, 0);
    // настраиваем отображение точек
    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    
    // проходимся по каждому пикселю
    for (int y = 0; y < static_cast<int>(HEIGHT); y++) {
        for (int x = 0; x < static_cast<int>(WIDTH); x++) {
            // проверяем входит ли точка в множество Мандельброта
            Complex z(0, 0);
            int i = 0;
            for (; i < ITER_COUNT && abs(z) < 2; i++)
                z = z * z + Complex((x - WIDTH / 2) / C_DIVISOR, (y - HEIGHT / 2) / C_DIVISOR);
            
            // если точка не входит, задаем ей цвет в зависимости от количества итераций    
            if (abs(z) >= 2) {
                HsvColor const hsv{ static_cast<unsigned char>(255 * i / ITER_COUNT), 255, 255 };
                RgbColor const rgb = HsvToRgb(hsv);
                    
                glColor3d(static_cast<double>(rgb.r) / 255,static_cast<double>(rgb.g) / 255,static_cast<double>(rgb.b) / 255);
                glVertex2d(x, y);
            }
            
            // в ином случае красим черным
            else {
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
    glOrtho(0, WIDTH, 0, HEIGHT, -1.0, 1.0); 
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(250, 100);
    glutInitWindowSize(static_cast<int>(WIDTH), static_cast<int>(HEIGHT));
    glutCreateWindow("Mandelbrot Set");
    glutReshapeFunc(resize);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
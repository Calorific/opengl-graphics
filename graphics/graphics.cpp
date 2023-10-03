#include <windows.h>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glut.h"

using namespace std;

void resize(int width, int height) {
    
}

void drawEllipse(const float cx, const float cy, const float rx, const float ry, const int numOfSegments) { 
    const float step = 2.0f * 3.1415926f / static_cast<float>(numOfSegments); 
    const float c = cosf(step); // заранее считаем косинус и синус
    const float s = sinf(step);

    float x = 1;
    float y = 0; 

    glBegin(GL_POLYGON); 
    for(int i = 0; i < numOfSegments; i++) { 
        glVertex2f(x * rx + cx, y * ry + cy); // отмечаем вершину

        // применяем матрицу вращения
        const float temp = x;
        x = c * x - s * y;
        y = s * temp + c * y;
    } 
    glEnd(); 
}

void display() {
    glColor3d(1, 1, 0);
    // glRotatef(45, 1, 1, 0);
    // glutSolidTeapot(2);
    // glutSolidCube(5);
    // glutSolidIcosahedron();
    // glutWireTorus(1, 3, 10, 10);

    
    // левый нижний квадрат
    glViewport(0, 0, 400, 400);

    // рисуем круглую точку
    glEnable(GL_POINT_SMOOTH);
    glPointSize(6);
    glBegin(GL_POINTS);
        glColor3d(1, 1, 0);
        glVertex3d(-3, 4, 0);

        
    glEnd();

    // рисуем большую точку
    glPointSize(14);
    glBegin(GL_POINTS); 
        glColor3d(0, 0, 1);
        glVertex3d(-5, -5, 0);
    glEnd();
    
    // рисуем квадратные точки
    glPointSize(6);
    glDisable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
        glColor3d(1, 0, 0);
        glVertex3d(3, 3, 0);

        glColor3d(0, 1, 0);
        glVertex3d(3, -4, 0);
    glEnd();

    // отображаем строку
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0, 0, 0); 
    glRasterPos2f(-3, 0);

    string s = "AVT-213";
    for (auto i = s.begin(); i != s.end(); ++i) 
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *i);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    
    // левый верхний квадрат
    glViewport(0, 400, 400, 400);
    
    // рисуем букву "О" - 2 эллипса, наложенные друг на друга
    glDisable(GL_DEPTH_TEST);
    glColor3d(0, 0, 0);
    drawEllipse(0, -3, 1, 1.2f, 100);
    glColor3d(1, 1, 1);
    drawEllipse(0, -3.01f, 0.7f, 0.84f, 100);

    // первая линия
    glBegin(GL_LINES);
        glColor3d(1, 1, 0);
        glVertex3d(-5, -1, 0);
        glVertex3d(4, 5, 0);
    glEnd();

    // вторая линия
    glLineWidth(6);
    glBegin(GL_LINES);
        glColor3d(0, 1, 0);
        glVertex3d(-2, -2, 0); 
        glVertex3d(5, 3, 0);
    glEnd();

    // третья прерывистая линия
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE); // разрешаем рисовать прерывистую линию
    glLineStipple(2, 58360); // устанавливаем маску
    glBegin(GL_LINES);
        glColor3d(1, 0, 0);
        glVertex3d(5, -3, 0);
        glVertex3d(-4, 4, 0);
    glEnd();
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);

    
    // правый нижний квадрат
    glViewport(400, 0, 400, 400);
    
    // рисуем ломаную
    glBegin(GL_LINE_STRIP);
        glColor3d(0, 0, 0);
        glVertex3d(-5, 4, 0);
        glVertex3d(-3, 5, 0);
        glVertex3d(-3, 3, 0);
        glVertex3d(-5, 2, 0);
        glVertex3d(-2, 5, 0);
        glVertex3d(-2, 2, 0);
    glEnd();

    // рисуем треугольник
    glBegin(GL_TRIANGLES);
        glColor3d(0, 0, 1);
        glVertex3d(2, 4, 0);
        glVertex3d(2, 5, 0);
        glVertex3d(4, 5, 0);
    glEnd();

    // рисуем четырехугольник
    glBegin(GL_POLYGON);
        glColor3d(1, 0.4, 0);
        glVertex3d(1, -1, 0);
        glVertex3d(4, -4, 0);
        glVertex3d(0, -5, 0);
        glVertex3d(-4, -3, 0);
    glEnd();

    
    // правый верхний квадрат
    glViewport(400, 400, 400, 400);
    
    // рисуем красные квадраты
    glBegin(GL_QUADS);
        glColor3d(1, 0, 0); 
    
        glVertex3d(-3, -1, 0);
        glVertex3d(-5, -1, 0);
        glVertex3d(-5, -3, 0);
        glVertex3d(-3, -3, 0);
        
        glVertex3d(-3, -1, 0);
        glVertex3d(-5, -1, 0);
        glVertex3d(-5, 1, 0);
        glVertex3d(-3, 1, 0);

        glVertex3d(-3, 1, 0);
        glVertex3d(-5, 1, 0);
        glVertex3d(-5, 3, 0);
        glVertex3d(-3, 3, 0);
    
        glVertex3d(-3, 3, 0);
        glVertex3d(-5, 3, 0);
        glVertex3d(-5, 5, 0);
        glVertex3d(-3, 5, 0);
    glEnd();

    // рисуем 6 разных треугольников
    glBegin(GL_TRIANGLES); 
        glColor3d(1, 0, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(2, 4, 0);
        glVertex3d(3, 3, 0);

        glColor3d(0, 1, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(3, 2, 0);
        glVertex3d(3, 3, 0);

        glColor3d(0, 0, 1);
        glVertex3d(0, 0, 0);
        glVertex3d(3, 2, 0);
        glVertex3d(3, 0, 0);
    
        glColor3d(1, 1, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(3, -1, 0);
        glVertex3d(3, 0, 0);

        glColor3d(1, 0, 1);
        glVertex3d(0, 0, 0);
        glVertex3d(3, -1, 0);
        glVertex3d(2, -2, 0);

        glColor3d(0, 1, 1);
        glVertex3d(0, 0, 0);
        glVertex3d(1, -3, 0);
        glVertex3d(2, -2, 0);
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
    glOrtho(-6.0, 6.0, -7.0, 5.0, 0, 12.0);
    gluLookAt(0, 0, 5, 0, 1, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(250, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Lab 1 - 2");
    glutReshapeFunc(resize);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

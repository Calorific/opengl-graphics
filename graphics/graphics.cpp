#include <iostream>
#include <ostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "stb_image.h"
#include "glut.h"

using namespace std;

#define PI 3.14159265358979323846

enum {
    width = 600,
    height = 600
};

GLfloat vertices[][3] = {
    {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0},
    {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}
};

GLfloat texCoords[][2] = {
    {0.0, 0.0}, {1.0, 0.0},
    {1.0, 1.0}, {0.0, 1.0}
};

GLuint textureID; // Идентификатор текстуры

int angle = 3;

// Загрузка текстуры
void loadTexture(const char* filename) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb);

    if (image != nullptr) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        stbi_image_free(image);
    } else {
        cout << "Texture loading error" << endl;
    }
}

void polygon(const int a, const int b, const int c, const int d) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_POLYGON);
    {
        glTexCoord2fv(texCoords[0]);  glVertex3fv(vertices[a]);
        glTexCoord2fv(texCoords[1]); glVertex3fv(vertices[b]);
        glTexCoord2fv(texCoords[2]); glVertex3fv(vertices[c]);
        glTexCoord2fv(texCoords[3]); glVertex3fv(vertices[d]);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void colorcube() {
    glEnable(GL_TEXTURE_2D); // Включаем использование текстур

    glBindTexture(GL_TEXTURE_2D, textureID);
    
    polygon(0, 3, 2, 1);
    polygon(2, 3, 7, 6);
    polygon(0, 4, 7, 3);
    polygon(1, 2, 6, 5);
    polygon(4, 5, 6, 7);
    polygon(0, 1, 5, 4);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D); // Выключаем использование текстур
}

void resize(int h, int w) {
}

void handleKeypress(const unsigned char key, int x, int y) {
    if (key == 'r') angle = (angle + 1) % 360;
    else if (key == 27) exit(EXIT_SUCCESS);
    glutPostRedisplay();
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // затираем рисунок фоном
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка буфера цвета и глубины
    glLoadIdentity(); // обнуление трансформации
    glShadeModel(GL_FLAT);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(2*cos(static_cast<double>(angle) / 180 * PI), 0.7, 2*sin(static_cast<double>(angle) / 180 * PI),
        0, 0, 0, 0, 1, 0);
    colorcube();
    
    glFlush();
}

void init() {
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1, 1, 1, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, 0, 20);
    glMatrixMode(GL_MODELVIEW);
}

int main() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 10);
    glutInitWindowSize(width, height);
    glutCreateWindow("Lab 3");
    glutReshapeFunc(resize);
    init();
    loadTexture("texture.png");
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
    return 0;
}

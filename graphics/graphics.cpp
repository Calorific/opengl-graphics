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

int theta = 3;
int phi = 10;
double radius = 3;

int mod(const int x, const int n){
    return (x % n + n) % n;
}

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
    glBegin(GL_QUADS);
    {
        glTexCoord2fv(texCoords[0]); glVertex3fv(vertices[a]);
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
    
    glColor3f(1, 1, 1);
    
    polygon(1, 0, 3, 2);
    polygon(2, 6, 5, 1);
    polygon(3, 7, 6, 2);
    polygon(0, 4, 5, 1);
    polygon(0, 3, 7, 4);
    polygon(7, 6, 5, 4);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D); // Выключаем использование текстур
}

void resize(int h, int w) {
}

void handleKeypress(const unsigned char key, int x, int y) {
    if (key == 'w') phi = mod(phi + 1, 360);
    else if (key == 'a') theta = mod(theta - 1, 360);
    else if (key == 's') phi = mod(phi - 1, 360);
    else if (key == 'd') theta = mod(theta + 1, 360);
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

    const double x = radius * sin(theta * PI / 180) * cos(phi * PI / 180);
    const double y = radius * sin(phi * PI / 180);
    const double z = radius * cos(theta * PI / 180) * cos(phi * PI / 180);
    
    gluLookAt(x, y, z,
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
    glutInitWindowPosition(100, 30);
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

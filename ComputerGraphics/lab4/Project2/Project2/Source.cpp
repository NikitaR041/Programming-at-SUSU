#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

float angleX = 0.0f, angleY = 0.0f;
int lastMouseX, lastMouseY;
GLuint textureID;

// Свет 1 (Направленный)
GLfloat light0_pos[] = { -2.0f, 2.0f, 0.0f, 0.0f };
GLfloat light0_diff[] = { 1.0f, 1.0f, 1.0f, 1.0f };

// Свет 2 (Точечный)
GLfloat light1_pos[] = { 2.0f, 0.0f, 2.0f, 1.0f };
GLfloat light1_diff[] = { 0.0f, 0.5f, 1.0f, 1.0f };

// Материал
GLfloat mat_diffuse[] = { 0.8f, 0.5f, 0.2f, 1.0f };
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float shininess = 32.0f;

void loadTexture(const char* filename) {
    int w, h, c;
    unsigned char* data = stbi_load(filename, &w, &h, &c, 4);
    if (!data) {
        cout << "Ошибка загрузки текстуры: " << filename << endl;
        return;
    }
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
}

void drawTexturedCube(float size) {
    float s = size / 2.0f;
    glBegin(GL_QUADS);
    // Передняя
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, s);
    // Задняя
    glNormal3f(0, 0, -1);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(-s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, s, -s);
    glTexCoord2f(0, 0); glVertex3f(s, -s, -s);
    // Верхняя
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 1); glVertex3f(-s, s, -s);
    glTexCoord2f(0, 0); glVertex3f(-s, s, s);
    glTexCoord2f(1, 0); glVertex3f(s, s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, -s);
    // Нижняя
    glNormal3f(0, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(-s, -s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, -s, -s);
    glTexCoord2f(0, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, s);
    // Правая
    glNormal3f(1, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, s, s);
    glTexCoord2f(0, 0); glVertex3f(s, -s, s);
    // Левая
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, s);
    glTexCoord2f(1, 1); glVertex3f(-s, s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, -s);
    glEnd();
}

void init() {
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    loadTexture("texture.jpg");
}

void reshape(int w, int h) { 
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0);

    glRotatef(angleX, 1, 0, 0);
    glRotatef(angleY, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    // Куб
    glBindTexture(GL_TEXTURE_2D, textureID);
    drawTexturedCube(1.5f);

    // Сфера
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(2.0f, 0, 0);
    glutSolidSphere(0.8, 40, 40);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': light1_pos[1] += 0.2f; break;
    case 's': light1_pos[1] -= 0.2f; break;
    case 'a': light1_pos[0] -= 0.2f; break;
    case 'd': light1_pos[0] += 0.2f; break;
    case '1': mat_diffuse[0] = 1; mat_diffuse[1] = 0; mat_diffuse[2] = 0; break;
    case '2': mat_diffuse[0] = 0; mat_diffuse[1] = 1; mat_diffuse[2] = 0; break;
    case '3': mat_diffuse[0] = 0; mat_diffuse[1] = 0; mat_diffuse[2] = 1; break;
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    angleY += (x - lastMouseX) * 0.5f;
    angleX += (y - lastMouseY) * 0.5f;
    lastMouseX = x;
    lastMouseY = y;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab 4: Fixed");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glutMainLoop();
    return 0;
}
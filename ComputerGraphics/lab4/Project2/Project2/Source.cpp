#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>

using namespace std;

// Глобальные переменные для состояния мыши
static int lastMouseX = 0;
static int lastMouseY = 0;

// Идентификатор текстуры 
GLuint textureID;

// --- Параметры освещения ---
// Источник 1: Направленный (w=0.0)
GLfloat light0_pos[4] = { -2.0f, 2.0f, 0.0f, 0.0f };
GLfloat light0_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light0_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

// Источник 2: Точечный (w=1.0) с затуханием
GLfloat light1_pos[4] = { 2.0f, 0.0f, 2.0f, 1.0f };
GLfloat light1_diffuse[4] = { 0.0f, 0.5f, 1.0f, 1.0f }; // Голубоватый
GLfloat light1_specular[4] = { 0.8f, 0.8f, 1.0f, 1.0f };
// Параметры затухания (constant, linear, quadratic)
GLfloat light1_attenuation[3] = { 1.0f, 0.1f, 0.05f };

bool light1_enabled = true; // Флаг включения/выключения второго источника

// --- Параметры материала ---
GLfloat mat_ambient[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat mat_diffuse[4] = { 0.8f, 0.5f, 0.2f, 1.0f };
GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess = 32.0f;

// Углы вращения и позиция камеры
float angleX = 0.0f, angleY = 0.0f;
float cameraZ = -6.0f;

// Загрузка текстуры
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

// Ручная отрисовка куба с нормалями и текстурными координатами
void drawTexturedCube(float size) {
    float s = size / 2.0f;
    glBegin(GL_QUADS);
    // Передняя грань (нормаль Z+)
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, s);
    glTexCoord2f(0, 1); glVertex3f(-s, s, s);
    // Задняя грань (нормаль Z-)
    glNormal3f(0, 0, -1);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, -s);
    glTexCoord2f(1, 1); glVertex3f(-s, s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, s, -s);
    glTexCoord2f(0, 0); glVertex3f(s, -s, -s);
    // Верх
    glNormal3f(0, 1, 0);
    glTexCoord2f(0, 1); glVertex3f(-s, s, -s);
    glTexCoord2f(0, 0); glVertex3f(-s, s, s);
    glTexCoord2f(1, 0); glVertex3f(s, s, s);
    glTexCoord2f(1, 1); glVertex3f(s, s, -s);
    // Низ
    glNormal3f(0, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(-s, -s, -s);
    glTexCoord2f(0, 1); glVertex3f(s, -s, -s);
    glTexCoord2f(0, 0); glVertex3f(s, -s, s);
    glTexCoord2f(1, 0); glVertex3f(-s, -s, s);
    glEnd();
}

// Инициализация освещения и текстур
void initLighting() {
    glewInit();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    if (light1_enabled) glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // Настройка источника №1
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Настройка источника №2
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    // Затухание для точечного источника
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, light1_attenuation[0]);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, light1_attenuation[1]);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, light1_attenuation[2]);

    // Режим смешивания текстуры и света
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    loadTexture("texture.jpg");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Камера
    gluLookAt(0.0, 0.0, -cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Установка позиций источников
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

    // Материал
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    // Объект 1: Куб с текстурой
    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textureID);
    drawTexturedCube(1.5f);
    glPopMatrix();

    // Объект 2: Сфера без текстуры (чистый свет)
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.5f, 0.0f, 0.0f);
    glutSolidSphere(0.8, 40, 40);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

    // --- Отрисовка текстовой информации (без освещения) ---
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    char buffer[256];
    // Позиция LIGHT0
    sprintf(buffer, "Light0 (dir): (%.1f, %.1f, %.1f)", light0_pos[0], light0_pos[1], light0_pos[2]);
    glRasterPos2f(-0.95f, 0.95f);
    for (int i = 0; buffer[i] != '\0'; i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);

    // Позиция LIGHT1
    sprintf(buffer, "Light1 (point): (%.1f, %.1f, %.1f) [%s]", light1_pos[0], light1_pos[1], light1_pos[2],
        light1_enabled ? "ON" : "OFF");
    glRasterPos2f(-0.95f, 0.88f);
    for (int i = 0; buffer[i] != '\0'; i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);

    // Блеск и цвет
    sprintf(buffer, "Shininess: %.0f | Color: R=%.1f G=%.1f B=%.1f", shininess, mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]);
    glRasterPos2f(-0.95f, 0.81f);
    for (int i = 0; buffer[i] != '\0'; i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);

    // Подсказки по управлению
    glRasterPos2f(-0.95f, -0.9f);
    const char* help = "W/A/S/D/Q/E - Light0 | T/G/F/H/R/Y - Light1 | 0 - toggle Light1 | +/- shininess | 1/2/3 color";
    for (int i = 0; help[i] != '\0'; i++) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, help[i]);

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Управление направленным светом (Light0)
    case 'w': light0_pos[1] += 0.2f; break;
    case 's': light0_pos[1] -= 0.2f; break;
    case 'a': light0_pos[0] -= 0.2f; break;
    case 'd': light0_pos[0] += 0.2f; break;
    case 'q': light0_pos[2] -= 0.2f; break;
    case 'e': light0_pos[2] += 0.2f; break;

        // Управление точечным светом (Light1) — дополнительное освещение
    case 't': light1_pos[1] += 0.2f; break;
    case 'g': light1_pos[1] -= 0.2f; break;
    case 'f': light1_pos[0] -= 0.2f; break;
    case 'h': light1_pos[0] += 0.2f; break;
    case 'r': light1_pos[2] -= 0.2f; break;
    case 'y': light1_pos[2] += 0.2f; break;

        // Включение/выключение второго источника
    case '0':
        light1_enabled = !light1_enabled;
        if (light1_enabled) glEnable(GL_LIGHT1);
        else glDisable(GL_LIGHT1);
        break;

        // Смена цвета материала
    case '1': mat_diffuse[0] = 1.0f; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 0.0f; break;
    case '2': mat_diffuse[0] = 0.0f; mat_diffuse[1] = 1.0f; mat_diffuse[2] = 0.0f; break;
    case '3': mat_diffuse[0] = 0.0f; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 1.0f; break;

        // Блеск
    case '+': if (shininess < 128.0f) shininess += 4.0f; break;
    case '-': if (shininess > 4.0f) shininess -= 4.0f; break;

    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
    }
}

void mouseMotion(int x, int y) {
    angleY += (x - lastMouseX) * 0.5f;
    angleX += (y - lastMouseY) * 0.5f;
    lastMouseX = x;
    lastMouseY = y;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL - Two Lights with Attenuation");

    initLighting();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    printf("=== UPGRADED LIGHTING ===\n");
    printf("Light0 (dir): W/A/S/D/Q/E\n");
    printf("Light1 (point): T/G/F/H/R/Y\n");
    printf("0 - toggle Light1\n");
    printf("1/2/3 - change material color\n");
    printf("+/- - change shininess\n");
    printf("Mouse - rotate scene\n");

    glutMainLoop();
    return 0;
}
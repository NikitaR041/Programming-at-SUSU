#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <stdio.h>

using namespace std;

// Глобальные переменные для хранения состояния мыши
static int lastMouseX = 0;
static int lastMouseY = 0;

// Идентификатор текстуры 
GLuint textureID;

// --- Параметры освещения (Задание 3 + Доп. требование) ---
// Источник 1: Направленный (w=0.0)
GLfloat light0_pos[4] = { -2.0f, 2.0f, 0.0f, 0.0f };
GLfloat light0_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light0_diffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light0_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

// Источник 2: Точечный (w=1.0) (Дополнительный источник)
GLfloat light1_pos[4] = { 2.0f, 0.0f, 2.0f, 1.0f };
GLfloat light1_diffuse[4] = { 0.0f, 0.5f, 1.0f, 1.0f }; // Голубоватый свет

// --- Параметры материала (Задание 4) ---
GLfloat mat_ambient[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat mat_diffuse[4] = { 0.8f, 0.5f, 0.2f, 1.0f };
GLfloat mat_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess = 32.0f;

// Углы вращения и позиция камеры 
float angleX = 0.0f, angleY = 0.0f;
float cameraZ = -6.0f;

// Функция загрузки текстуры 
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

// Функция ручной отрисовки куба с нормалями и текстурными координатами
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
    // Остальные грани
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

// Инициализация освещения и доп. параметров
void initLighting() {
    glewInit(); // Инициализация GLEW для корректной работы расширений
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1); // Включаем второй свет
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    // Настройка источника №1
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Настройка источника №2
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    // Режим взаимодействия текстуры и света
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    loadTexture("texture.jpg");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Настройка камеры (из базового кода)
    gluLookAt(0.0, 0.0, -cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Обновление позиций ламп
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

    // Применяем свойства материала
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    // Объект 1: Куб (с текстурой)
    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, textureID);
    drawTexturedCube(1.5f);
    glPopMatrix();

    // Объект 2: Сфера (без текстуры, чтобы видеть чистый свет)
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(1.5f, 0.0f, 0.0f);
    glutSolidSphere(0.8, 40, 40);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);

    // Отрисовка текста 
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);

    char buffer[256];
    sprintf(buffer, "Light 0 Pos: (%.1f, %.1f, %.1f)", light0_pos[0], light0_pos[1], light0_pos[2]);
    glRasterPos2f(-0.9f, 0.9f);
    for (int i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);

    sprintf(buffer, "Shininess: %.0f | Colors: 1,2,3", shininess);
    glRasterPos2f(-0.9f, 0.82f);
    for (int i = 0; buffer[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);

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
        // Управление основным светом
    case 'w': light0_pos[1] += 0.2f; break;
    case 's': light0_pos[1] -= 0.2f; break;
    case 'a': light0_pos[0] -= 0.2f; break;
    case 'd': light0_pos[0] += 0.2f; break;
    case 'q': light0_pos[2] -= 0.2f; break;
    case 'e': light0_pos[2] += 0.2f; break;

        // Переключение цветов материала
    case '1': mat_diffuse[0] = 1; mat_diffuse[1] = 0; mat_diffuse[2] = 0; break; // Красный
    case '2': mat_diffuse[0] = 0; mat_diffuse[1] = 1; mat_diffuse[2] = 0; break; // Зеленый
    case '3': mat_diffuse[0] = 0; mat_diffuse[1] = 0; mat_diffuse[2] = 1; break; // Синий

        // Блеск и выход
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
    glutCreateWindow("OpenGL 2.0 Phong Lighting - Texture & 2 Lights");

    initLighting(); // Объединенная инициализация

    // Регистрация всех функций
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion); // Важно для вращения!

    printf("Controls:\nW/A/S/D/Q/E - Move Light 0\n1/2/3 - Change Material Color\n+/- - Shininess\nMouse - Rotate Scene\n");

    glutMainLoop();
    return 0;
}
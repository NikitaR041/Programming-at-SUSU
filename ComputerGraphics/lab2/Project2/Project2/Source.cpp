#define _CRT_SECURE_NO_WARNINGS
#define GLEW_STATIC
#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>

using namespace std;

// Определение M_PI для совместимости
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ===================== ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ =====================

int width = 800;
int height = 600;

// Параметры камеры
float cameraAngle = 0.0f;
float cameraRadius = 15.0f;
int autoRotate = 0; // Автоматическое вращение выключено по умолчанию

// Параметры проекции
int isPerspective = 1; // 1 = Перспектива, 0 = Ортогональная
float fov = 45.0f;

// Параметры отсечения
const float NEAR_PLANE = 0.5f;
const float FAR_PLANE = 60.0f;

// ====================== ОТРИСОВКА ТЕКСТА ======================

void drawText(const char* text, int x, int y) {
    glRasterPos2i(x, y);
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

// ====================== ОСНОВНАЯ СЦЕНА ======================
// Каркасный куб в центре и сфера над ним, смещенная по Z

void drawMainScene() {
    // ----- КАРКАСНЫЙ КУБ В ЦЕНТРЕ -----
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f); // В центре координат
    glColor3f(1.0f, 1.0f, 1.0f); // Белый цвет
    glutWireCube(2.0); // Куб размером 2
    glPopMatrix();

    // ----- СФЕРА НАД КУБОМ, СМЕЩЕННАЯ ПО Z -----
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, -2.0f); // Смещение: Y=2 (вверх), Z=-2 (вглубь)
    glColor3f(0.0f, 1.0f, 1.0f); // Голубой цвет
    glutWireSphere(1.0, 20, 20); // Сфера радиусом 1
    glPopMatrix();

    // Добавим небольшую сферу-указатель в центр для ориентации
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
    glutSolidSphere(0.2, 10, 10); // Маленькая точка в центре
    glPopMatrix();
}

// ==================== СЦЕНА ИЗ 5 КУБОВ ====================
void drawFiveCubesScene() {

    // Куб 1: Ближний, красный (Z = -5)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutWireCube(1.0);
    glPopMatrix();

    // Куб 2: Средний ближний, зеленый (Z = -10)
    glPushMatrix();
    glTranslatef(-3.0f, 2.0f, -10.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glutWireCube(1.5);
    glPopMatrix();

    // Куб 3: Центральный, синий (Z = -15)
    glPushMatrix();
    glTranslatef(3.0f, -2.0f, -15.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireCube(2.0);
    glPopMatrix();

    // Куб 4: Дальний, желтый (Z = -20)
    glPushMatrix();
    glTranslatef(-4.0f, 0.0f, -20.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutWireCube(2.5);
    glPopMatrix();

    // Куб 5: Самый дальний, фиолетовый (Z = -25)
    glPushMatrix();
    glTranslatef(4.0f, 3.0f, -25.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    glutWireCube(3.0);
    glPopMatrix();
}

// ===================== ОТРИСОВКА ОСЕЙ =====================

void drawAxes() {
    glBegin(GL_LINES);
    // Ось X (красная)
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(5, 0, 0);
    // Ось Y (зеленая)
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 5, 0);
    // Ось Z (синяя)
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 5);

    // Отрицательные направления (пунктирно - более тонкие линии)
    glColor3f(0.5f, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(-5, 0, 0);

    glColor3f(0, 0.5f, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, -5, 0);

    glColor3f(0, 0, 0.5f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -5);
    glEnd();

    // Подписи осей
    glColor3f(1, 1, 1);
    glRasterPos3f(5.5f, 0, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
    glRasterPos3f(0, 5.5f, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
    glRasterPos3f(0, 0, 5.5f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
}

// =================== ИЗМЕНЕНИЕ РАЗМЕРА ОКНА И ПРОЕКЦИИ ===================

void reshape(int w, int h) {
    width = w;
    height = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (isPerspective) {
        // Перспективная проекция
        float aspect = (GLfloat)w / (GLfloat)h;
        gluPerspective(fov, aspect, NEAR_PLANE, FAR_PLANE);
    }
    else {
        // Ортогональная проекция
        float aspect = (GLfloat)w / (GLfloat)h;
        if (w <= h)
            glOrtho(-10.0, 10.0, -10.0 / aspect, 10.0 / aspect, NEAR_PLANE, FAR_PLANE);
        else
            glOrtho(-10.0 * aspect, 10.0 * aspect, -10.0, 10.0, NEAR_PLANE, FAR_PLANE);
    }

    glMatrixMode(GL_MODELVIEW);
}

// ===================== ГЛАВНАЯ ФУНКЦИЯ ОТРИСОВКИ =====================

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Настройка камеры
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Позиция камеры (вращается вокруг сцены если включено)
    float camX = cameraRadius * sin(cameraAngle * M_PI / 180.0);
    float camZ = cameraRadius * cos(cameraAngle * M_PI / 180.0);

    // Устанавливаем камеру: позиция (camX, 5, camZ), смотрим на центр (0,0,0)
    gluLookAt(camX, 5.0, camZ,  // позиция камеры
        0.0, 0.0, 0.0,    // точка, на которую смотрим
        0.0, 1.0, 0.0);   // вектор "вверх"

    // Основная сцена (центр)
    drawMainScene();

    // Сцена из 5 кубов (глубина)
    drawFiveCubesScene();

    // Оси координат
    drawAxes();

    // ===================== ОТРИСОВКА ИНТЕРФЕЙСА (2D) =====================

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Статус и информация
    glColor3f(0.0f, 1.0f, 1.0f);
    char buffer[200];
    int yPos = height - 30;

    sprintf(buffer, "=== LAB 2: 3D TRANSFORMATIONS ===");
    drawText(buffer, 10, yPos); yPos -= 25;

    sprintf(buffer, "Projection: %s", isPerspective ? "PERSPECTIVE" : "ORTHOGRAPHIC");
    drawText(buffer, 10, yPos); yPos -= 25;

    sprintf(buffer, "Camera Angle: %.1f deg | Auto Rotate: %s",
        cameraAngle, autoRotate ? "ON" : "OFF");
    drawText(buffer, 10, yPos); yPos -= 25;

    sprintf(buffer, "FOV: %.1f deg | Near: %.1f | Far: %.1f", fov, NEAR_PLANE, FAR_PLANE);
    drawText(buffer, 10, yPos); yPos -= 25;

    // Описание сцены
    glColor3f(1.0f, 1.0f, 0.0f);
    yPos -= 20;
    drawText("SCENE: Wireframe Cube at center (0,0,0)", 10, yPos); yPos -= 20;
    drawText("Sphere above cube: at (0, 2, -2)", 10, yPos); yPos -= 20;
    drawText("Red dot at origin (0,0,0) for reference", 10, yPos); yPos -= 20;

    // Управление
    glColor3f(0.0f, 1.0f, 0.0f);
    yPos -= 20;
    drawText("CONTROLS:", 10, yPos); yPos -= 20;
    drawText("[P] Switch Projection | [+/-] Change FOV", 10, yPos); yPos -= 20;
    drawText("[R] Toggle Auto Rotation | [Arrow Keys] Manual Rotation", 10, yPos); yPos -= 20;
    drawText("[ESC] Exit", 10, yPos);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

// ===================== АНИМАЦИЯ =====================

void idle() {
    if (autoRotate) {
        cameraAngle += 0.3f;
        if (cameraAngle >= 360.0f) cameraAngle -= 360.0f;
    }
    glutPostRedisplay();
}

// =================== УПРАВЛЕНИЕ КЛАВИАТУРОЙ ===================

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Переключение проекции
    case 'p':
    case 'P':
        isPerspective = !isPerspective;
        reshape(width, height);
        break;

        // Управление FOV
    case '+':
    case '=':
        fov += 5.0f;
        if (fov > 120.0f) fov = 120.0f;
        reshape(width, height);
        break;
    case '-':
    case '_':
        fov -= 5.0f;
        if (fov < 10.0f) fov = 10.0f;
        reshape(width, height);
        break;

        // Включение/выключение вращения
    case 'r':
    case 'R':
        autoRotate = !autoRotate;
        break;

    case 27: // ESC
        exit(0);
        break;
    }

    glutPostRedisplay();
}

// =================== УПРАВЛЕНИЕ СПЕЦИАЛЬНЫМИ КЛАВИШАМИ ===================

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        cameraAngle += 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngle -= 5.0f;
        break;
    case GLUT_KEY_UP:
        cameraRadius -= 1.0f;
        if (cameraRadius < 5.0f) cameraRadius = 5.0f;
        break;
    case GLUT_KEY_DOWN:
        cameraRadius += 1.0f;
        if (cameraRadius > 30.0f) cameraRadius = 30.0f;
        break;
    }

    glutPostRedisplay();
}

// ======================= ИНИЦИАЛИЗАЦИЯ =======================

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Lab 2 - Cube and Sphere");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idle);

    printf("=== Lab 2: Cube and Sphere ===\n");
    printf("Scene: Wireframe cube at origin, sphere at (0, 2, -2)\n");
    printf("Controls:\n");
    printf("  P - Switch Perspective/Orthographic\n");
    printf("  +/- - Change FOV (Field of View)\n");
    printf("  R - Toggle auto rotation\n");
    printf("  Arrow Keys - Manual camera control\n");
    printf("  ESC - Exit\n");

    glutMainLoop();
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

using namespace std;

// --- Игрок ---
float posX = 1.5f, posZ = 1.5f, angle = 0.0f;
float playerRadius = 0.18f, speed = 0.12f;

// --- Монета (Анимированная с физикой) ---
float coinAngle = 0.0f;
float coinX = 1.0f, coinZ = 1.0f; // Начальная позиция
float coinSpeed = 0.04f;          // Скорость движения монеты
float coinDirZ = 1.0f;            // Направление движения (1 или -1)
float coinRadius = 0.25f;         // Радиус самой монеты (для коллизий)

// --- Лабиринт ---
const int MAZE_WIDTH = 10, MAZE_HEIGHT = 10;
int maze[10][10] = {
    {1,1,1,1,1,1,1,1,1,1}, {1,0,0,0,1,0,0,0,0,1}, {1,0,1,0,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,1,0,1}, {1,0,1,1,1,1,0,1,0,1}, {1,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,0,1,1,1,0,1}, {1,0,0,0,0,0,0,1,0,1}, {1,0,1,1,1,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

GLuint wallTexture, coinTexture;

void loadTexture(const char* filename, GLuint& id) {
    int w, h, c;
    unsigned char* data = stbi_load(filename, &w, &h, &c, 4);
    if (!data) return;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

// Функция отрисовки вертикальной монетки и тени
void drawVerticalCoin(float x, float z) {
    // 1. ТЕНЬ - остается горизонтальной
    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(x, 0.01f, z);
    glRotatef(90, 1, 0, 0); // Тень лежит
    glScalef(1.0f, 2.0f, 0.1f); // Делаем плоской
    GLUquadric* qShadow = gluNewQuadric();
    gluDisk(qShadow, 0, 0.3, 30, 1);
    glPopMatrix();
    glDisable(GL_BLEND); glEnable(GL_LIGHTING); glEnable(GL_TEXTURE_2D); glColor3f(1, 1, 1);

    // 2. МОНЕТА (Вертикальная)
    glPushMatrix();
    // Поднимаем центр монеты, чтобы она катилась по полу, а не висела
    glTranslatef(x, coinRadius, z);

    // Вращение вокруг своей оси (как колесо)
    glRotatef(coinAngle, 0, 1, 0);

    GLfloat mat_spec[] = { 1.0f, 1.0f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glBindTexture(GL_TEXTURE_2D, coinTexture);
    GLUquadric* qCoin = gluNewQuadric();
    gluQuadricTexture(qCoin, GL_TRUE);

    // Отрисовка цилиндра (тело монеты)
    glTranslatef(0, 0, -0.025f); // Центрируем толщину
    gluCylinder(qCoin, coinRadius, coinRadius, 0.05, 30, 1);

    // Крышки
    gluDisk(qCoin, 0, coinRadius, 30, 1);
    glTranslatef(0, 0, 0.05f);
    gluDisk(qCoin, 0, coinRadius, 30, 1);

    gluDeleteQuadric(qCoin);
    glPopMatrix();
}

void timer(int v) {
    // 1. Анимация вращения
    coinAngle += 5.0f;
    if (coinAngle > 360) coinAngle -= 360;

    // 2. Физика движения и коллизий
    float nextZ = coinZ + coinSpeed * coinDirZ;

    // Проверяем клетку, куда монета хочет попасть (с учетом её радиуса)
    int checkGridZ = (int)(nextZ + (coinRadius * coinDirZ) + 0.5f);
    int currentGridX = (int)(coinX + 0.5f);

    // Убеждаемся, что мы в границах массива
    if (checkGridZ >= 0 && checkGridZ < MAZE_HEIGHT) {
        if (maze[currentGridX][checkGridZ] == 0) {
            // Путь свободен - едем
            coinZ = nextZ;
        }
        else {
            // СТЕНА! Отскакиваем (меняем направление)
            coinDirZ *= -1.0f;
            // Немного сдвигаем назад, чтобы не застрять в текстуре стенки
            coinZ += coinSpeed * coinDirZ;
        }
    }
    else {
        // Край карты - тоже отскок
        coinDirZ *= -1.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// Функции display, keyboard, reshape и main не изменились с прошлого раза...
// Но для удобства вот обновленный display с вызовом новой функции
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(posX, 0.5f, posZ, posX + sin(angle), 0.5f, posZ - cos(angle), 0, 1, 0);

    GLfloat lightPos[] = { posX, 0.5f, posZ, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glBindTexture(GL_TEXTURE_2D, wallTexture);
    for (int i = 0; i < MAZE_WIDTH; i++) {
        for (int j = 0; j < MAZE_HEIGHT; j++) {
            if (maze[i][j] == 1) {
                float s = 0.5f;
                glPushMatrix(); glTranslatef(i, 0.5f, j);
                glBegin(GL_QUADS);
                glNormal3f(0, 0, 1); glTexCoord2f(0, 0); glVertex3f(-s, -s, s); glTexCoord2f(1, 0); glVertex3f(s, -s, s); glTexCoord2f(1, 1); glVertex3f(s, s, s); glTexCoord2f(0, 1); glVertex3f(-s, s, s);
                glNormal3f(0, 0, -1); glTexCoord2f(0, 0); glVertex3f(-s, -s, -s); glTexCoord2f(1, 0); glVertex3f(s, -s, -s); glTexCoord2f(1, 1); glVertex3f(s, s, -s); glTexCoord2f(0, 1); glVertex3f(-s, s, -s);
                glNormal3f(1, 0, 0); glTexCoord2f(0, 0); glVertex3f(s, -s, -s); glTexCoord2f(1, 0); glVertex3f(s, s, -s); glTexCoord2f(1, 1); glVertex3f(s, s, s); glTexCoord2f(0, 1); glVertex3f(s, -s, s);
                glNormal3f(-1, 0, 0); glTexCoord2f(0, 0); glVertex3f(-s, -s, -s); glTexCoord2f(1, 0); glVertex3f(-s, s, -s); glTexCoord2f(1, 1); glVertex3f(-s, s, s); glTexCoord2f(0, 1); glVertex3f(-s, -s, -s);
                glEnd(); glPopMatrix();
            }
            else {
                glDisable(GL_TEXTURE_2D); glColor3f(0.2f, 0.2f, 0.2f);
                glBegin(GL_QUADS); glNormal3f(0, 1, 0); glVertex3f(i - 0.5f, 0, j - 0.5f); glVertex3f(i + 0.5f, 0, j - 0.5f); glVertex3f(i + 0.5f, 0, j + 0.5f); glVertex3f(i - 0.5f, 0, j + 0.5f); glEnd();
                glEnable(GL_TEXTURE_2D); glColor3f(1, 1, 1);
            }
        }
    }

    drawVerticalCoin(coinX, coinZ); // Вызов обновленной функции
    glutSwapBuffers();
}

// Оставшиеся функции (keyboard, reshape, main) берем из предыдущего рабочего кода.
// Убедись, что в коллизиях игрока в keyboard() используется корректное округление (int)(nX + 0.5f).

void keyboard(unsigned char key, int x, int y) {
    float nX = posX, nZ = posZ;
    if (key == 'w') { nX += sin(angle) * speed; nZ -= cos(angle) * speed; }
    if (key == 's') { nX -= sin(angle) * speed; nZ += cos(angle) * speed; }
    if (key == 'a') angle -= 0.1f;
    if (key == 'd') angle += 0.1f;

    // Простая коллизия для игрока (для WASD)
    if (maze[(int)(nX + 0.5f)][(int)(posZ + 0.5f)] == 0) posX = nX;
    if (maze[(int)(posX + 0.5f)][(int)(nZ + 0.5f)] == 0) posZ = nZ;

    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Vertical Coin Physics");
    glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING); glEnable(GL_LIGHT0); glEnable(GL_TEXTURE_2D);
    loadTexture("stena.jpg", wallTexture);
    loadTexture("yellow.jpg", coinTexture);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
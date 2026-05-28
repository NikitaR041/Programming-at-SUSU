//#define _CRT_SECURE_NO_WARNINGS
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include <iostream>
//#include <cmath>
//
//using namespace std;
//
//const float PI = 3.14159265f;
//
//// --- Состояние игры ---
//enum GameState { MENU, PLAYING };
//GameState currentState = MENU;
//
//// --- Режим камеры: вид от 1-го или 3-го лица ---
//enum CameraMode { FIRST_PERSON, THIRD_PERSON };
//CameraMode cameraMode = FIRST_PERSON;
//
//// --- Координаты кнопки меню ---
//float btnLeft = -0.3f, btnRight = 0.3f;
//float btnTop = 0.05f, btnBottom = -0.15f;
//
//// --- Игрок ---
//float posX = 1.5f, posZ = 1.5f, angle = 0.0f;
//float playerRadius = 0.18f, speed = 0.12f;
//
//// --- Монета (анимированная, с физикой) ---
//float coinAngle = 0.0f;
//float coinX = 1.0f, coinZ = 1.0f;   // позиция
//float coinSpeed = 0.04f;            // скорость движения монеты
//float coinDirZ = 1.0f;              // направление движения (1 или -1)
//float coinRadius = 0.25f;           // радиус монеты (для коллизий)
//
//// --- Лабиринт ---
//const int MAZE_WIDTH = 10, MAZE_HEIGHT = 10;
//int maze[10][10] = {
//    {1,1,1,1,1,1,1,1,1,1},
//    {1,0,0,0,1,0,0,0,0,1},
//    {1,0,1,0,1,0,1,1,0,1},
//    {1,0,1,0,0,0,0,1,0,1},
//    {1,0,1,1,1,1,0,1,0,1},
//    {1,0,0,0,0,1,0,0,0,1},
//    {1,1,1,1,0,1,1,1,0,1},
//    {1,0,0,0,0,0,0,1,0,1},
//    {1,0,1,1,1,1,0,0,0,1},
//    {1,1,1,1,1,1,1,1,1,1}
//};
//
//GLuint wallTexture, coinTexture;
//
//void loadTexture(const char* filename, GLuint& id) {
//    int w, h, c;
//    unsigned char* data = stbi_load(filename, &w, &h, &c, 4);
//    if (!data) { cout << "Не удалось загрузить: " << filename << endl; return; }
//    glGenTextures(1, &id);
//    glBindTexture(GL_TEXTURE_2D, id);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//    stbi_image_free(data);
//}
//
//// --- Отрисовка вертикальной монетки и её тени ---
//void drawVerticalCoin(float x, float z) {
//    // 1. ТЕНЬ — лежит на полу
//    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
//    glPushMatrix();
//    glTranslatef(x, 0.01f, z);
//    glRotatef(90, 1, 0, 0);          // тень лежит горизонтально
//    glScalef(1.0f, 2.0f, 0.1f);      // делаем плоской/вытянутой
//    GLUquadric* qShadow = gluNewQuadric();
//    gluDisk(qShadow, 0, 0.3, 30, 1);
//    gluDeleteQuadric(qShadow);
//    glPopMatrix();
//    glDisable(GL_BLEND); glEnable(GL_LIGHTING); glEnable(GL_TEXTURE_2D); glColor3f(1, 1, 1);
//
//    // 2. МОНЕТА (вертикальная, катится как колесо)
//    glPushMatrix();
//    glTranslatef(x, coinRadius, z);  // поднимаем центр, чтобы катилась по полу
//    glRotatef(coinAngle, 0, 1, 0);   // вращение вокруг своей оси
//
//    GLfloat mat_spec[] = { 1.0f, 1.0f, 0.5f, 1.0f };
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
//    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);
//
//    glBindTexture(GL_TEXTURE_2D, coinTexture);
//    GLUquadric* qCoin = gluNewQuadric();
//    gluQuadricTexture(qCoin, GL_TRUE);
//
//    glTranslatef(0, 0, -0.025f);                 // центрируем толщину
//    gluCylinder(qCoin, coinRadius, coinRadius, 0.05, 30, 1);
//    gluDisk(qCoin, 0, coinRadius, 30, 1);        // задняя крышка
//    glTranslatef(0, 0, 0.05f);
//    gluDisk(qCoin, 0, coinRadius, 30, 1);        // передняя крышка
//
//    gluDeleteQuadric(qCoin);
//    glPopMatrix();
//}
//
//// --- Отрисовка персонажа (видна только в 3-м лице) с тенью ---
//void drawPlayer() {
//    // 1. ТЕНЬ персонажа
//    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
//    glPushMatrix();
//    glTranslatef(posX, 0.02f, posZ);
//    glRotatef(90, 1, 0, 0);                      // тень лежит на полу
//    GLUquadric* qSh = gluNewQuadric();
//    gluDisk(qSh, 0, playerRadius * 1.3f, 30, 1);
//    gluDeleteQuadric(qSh);
//    glPopMatrix();
//    glDisable(GL_BLEND); glEnable(GL_LIGHTING);
//
//    // 2. ТЕЛО персонажа
//    glPushMatrix();
//    glTranslatef(posX, 0.0f, posZ);
//    glRotatef(-angle * 180.0f / PI, 0, 1, 0);    // поворот в сторону взгляда
//
//    // Туловище — цилиндр
//    glColor3f(0.15f, 0.45f, 0.9f);
//    glPushMatrix();
//    glRotatef(-90, 1, 0, 0);                     // ставим цилиндр вертикально
//    GLUquadric* qBody = gluNewQuadric();
//    gluCylinder(qBody, playerRadius, playerRadius * 0.6f, 0.5f, 20, 1);
//    gluDeleteQuadric(qBody);
//    glPopMatrix();
//
//    // Голова — сфера
//    glColor3f(1.0f, 0.82f, 0.6f);
//    glPushMatrix();
//    glTranslatef(0.0f, 0.62f, 0.0f);
//    glutSolidSphere(0.13f, 20, 20);
//    glPopMatrix();
//
//    // "Нос" — конус, показывает направление взгляда (-Z)
//    glColor3f(0.9f, 0.2f, 0.2f);
//    glPushMatrix();
//    glTranslatef(0.0f, 0.62f, -0.10f);
//    glRotatef(180, 0, 1, 0);                     // разворачиваем конус на -Z
//    glutSolidCone(0.05f, 0.15f, 12, 6);
//    glPopMatrix();
//
//    glPopMatrix();
//    glColor3f(1, 1, 1);
//    glEnable(GL_TEXTURE_2D);
//}
//
//void timer(int v) {
//    // 1. Анимация вращения монеты
//    coinAngle += 5.0f;
//    if (coinAngle > 360) coinAngle -= 360;
//
//    // 2. Физика движения монеты + коллизии со стенами
//    float nextZ = coinZ + coinSpeed * coinDirZ;
//    int checkGridZ = (int)(nextZ + (coinRadius * coinDirZ) + 0.5f);
//    int currentGridX = (int)(coinX + 0.5f);
//
//    if (checkGridZ >= 0 && checkGridZ < MAZE_HEIGHT) {
//        if (maze[currentGridX][checkGridZ] == 0) {
//            coinZ = nextZ;
//        }
//        else {
//            coinDirZ *= -1.0f;
//            coinZ += coinSpeed * coinDirZ;
//        }
//    }
//    else {
//        coinDirZ *= -1.0f;
//    }
//
//    glutPostRedisplay();
//    glutTimerFunc(16, timer, 0);
//}
//
//void mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        // Экранные координаты -> координаты OpenGL (-1..1)
//        float openGL_X = ((float)x / 1024.0f) * 2.0f - 1.0f;
//        float openGL_Y = 1.0f - ((float)y / 768.0f) * 2.0f;
//
//        // Проверка попадания клика в кнопку "Играть"
//        if (currentState == MENU &&
//            openGL_X > btnLeft && openGL_X < btnRight &&
//            openGL_Y > btnBottom && openGL_Y < btnTop) {
//            currentState = PLAYING;
//            glutPostRedisplay();
//        }
//    }
//}
//
//// --- Вывод текста ---
//void drawText(float x, float y, const char* str, void* font) {
//    glRasterPos2f(x, y);
//    for (int i = 0; str[i] != '\0'; i++)
//        glutBitmapCharacter(font, str[i]);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    if (currentState == MENU) {
//        // --- 2D-режим для меню ---
//        glMatrixMode(GL_PROJECTION);
//        glPushMatrix();
//        glLoadIdentity();
//        gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
//        glMatrixMode(GL_MODELVIEW);
//        glPushMatrix();
//        glLoadIdentity();
//
//        glDisable(GL_LIGHTING);
//        glDisable(GL_TEXTURE_2D);
//
//        // Заголовок
//        glColor3f(1.0f, 1.0f, 1.0f);
//        drawText(-0.32f, 0.45f, "3D LABYRINTH GAME", GLUT_BITMAP_TIMES_ROMAN_24);
//
//        // Кнопка "Играть"
//        glColor3f(0.2f, 0.2f, 0.8f);
//        glBegin(GL_QUADS);
//        glVertex2f(btnLeft, btnBottom);
//        glVertex2f(btnRight, btnBottom);
//        glVertex2f(btnRight, btnTop);
//        glVertex2f(btnLeft, btnTop);
//        glEnd();
//
//        // Текст на кнопке
//        glColor3f(1.0f, 1.0f, 1.0f);
//        drawText(-0.16f, -0.06f, "PLAY GAME", GLUT_BITMAP_HELVETICA_18);
//
//        // Подсказка по управлению
//        glColor3f(0.8f, 0.8f, 0.8f);
//        drawText(-0.45f, -0.40f, "Mouse - click PLAY    WASD - move", GLUT_BITMAP_HELVETICA_12);
//        drawText(-0.45f, -0.50f, "V - switch view (1st / 3rd person)", GLUT_BITMAP_HELVETICA_12);
//
//        // Возврат настроек
//        glPopMatrix();
//        glMatrixMode(GL_PROJECTION);
//        glPopMatrix();
//        glMatrixMode(GL_MODELVIEW);
//        glEnable(GL_LIGHTING);
//        glEnable(GL_TEXTURE_2D);
//    }
//    else {
//        // --- 3D-режим (игра) ---
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        gluPerspective(60.0, 1024.0 / 768.0, 0.1, 100.0);
//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();
//
//        // === КАМЕРА: вид от 1-го или 3-го лица ===
//        if (cameraMode == FIRST_PERSON) {
//            gluLookAt(posX, 0.5f, posZ,
//                      posX + sin(angle), 0.5f, posZ - cos(angle),
//                      0, 1, 0);
//        }
//        else { // THIRD_PERSON — камера позади и выше игрока
//            float dist = 1.4f;
//            // не даём камере провалиться сквозь стену
//            while (dist > 0.3f) {
//                float cx = posX - sin(angle) * dist;
//                float cz = posZ + cos(angle) * dist;
//                int gx = (int)(cx + 0.5f), gz = (int)(cz + 0.5f);
//                if (gx >= 0 && gx < MAZE_WIDTH && gz >= 0 && gz < MAZE_HEIGHT
//                    && maze[gx][gz] == 0)
//                    break;
//                dist -= 0.1f;
//            }
//            float camX = posX - sin(angle) * dist;
//            float camZ = posZ + cos(angle) * dist;
//            gluLookAt(camX, 1.1f, camZ,      // позиция камеры
//                      posX, 0.45f, posZ,     // смотрим на игрока
//                      0, 1, 0);
//        }
//
//        GLfloat lightPos[] = { posX, 0.8f, posZ, 1.0f };
//        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
//
//        // --- Отрисовка лабиринта ---
//        glBindTexture(GL_TEXTURE_2D, wallTexture);
//        for (int i = 0; i < MAZE_WIDTH; i++) {
//            for (int j = 0; j < MAZE_HEIGHT; j++) {
//                if (maze[i][j] == 1) {
//                    float s = 0.5f;
//                    glPushMatrix(); glTranslatef(i, 0.5f, j);
//                    glBegin(GL_QUADS);
//                    glNormal3f(0, 0, 1);  glTexCoord2f(0, 0); glVertex3f(-s, -s, s);  glTexCoord2f(1, 0); glVertex3f(s, -s, s);  glTexCoord2f(1, 1); glVertex3f(s, s, s);  glTexCoord2f(0, 1); glVertex3f(-s, s, s);
//                    glNormal3f(0, 0, -1); glTexCoord2f(0, 0); glVertex3f(-s, -s, -s); glTexCoord2f(1, 0); glVertex3f(s, -s, -s); glTexCoord2f(1, 1); glVertex3f(s, s, -s); glTexCoord2f(0, 1); glVertex3f(-s, s, -s);
//                    glNormal3f(1, 0, 0);  glTexCoord2f(0, 0); glVertex3f(s, -s, -s);  glTexCoord2f(1, 0); glVertex3f(s, s, -s);  glTexCoord2f(1, 1); glVertex3f(s, s, s);  glTexCoord2f(0, 1); glVertex3f(s, -s, s);
//                    glNormal3f(-1, 0, 0); glTexCoord2f(0, 0); glVertex3f(-s, -s, -s); glTexCoord2f(1, 0); glVertex3f(-s, s, -s); glTexCoord2f(1, 1); glVertex3f(-s, s, s); glTexCoord2f(0, 1); glVertex3f(-s, -s, -s);
//                    glEnd(); glPopMatrix();
//                }
//                else {
//                    glDisable(GL_TEXTURE_2D); glColor3f(0.2f, 0.2f, 0.2f);
//                    glBegin(GL_QUADS); glNormal3f(0, 1, 0);
//                    glVertex3f(i - 0.5f, 0, j - 0.5f); glVertex3f(i + 0.5f, 0, j - 0.5f);
//                    glVertex3f(i + 0.5f, 0, j + 0.5f); glVertex3f(i - 0.5f, 0, j + 0.5f);
//                    glEnd();
//                    glEnable(GL_TEXTURE_2D); glColor3f(1, 1, 1);
//                }
//            }
//        }
//
//        // Монета с тенью
//        drawVerticalCoin(coinX, coinZ);
//
//        // Персонаж рисуется только в виде от 3-го лица
//        if (cameraMode == THIRD_PERSON)
//            drawPlayer();
//    }
//    glutSwapBuffers();
//}
//
//void keyboard(unsigned char key, int x, int y) {
//    if (key == 27) exit(0); // ESC — выход
//
//    if (currentState == MENU) {
//        if (key == 13) { // ENTER — тоже запускает игру
//            currentState = PLAYING;
//            glutPostRedisplay();
//        }
//    }
//    else if (currentState == PLAYING) {
//        // Переключение вида камеры
//        if (key == 'v' || key == 'V')
//            cameraMode = (cameraMode == FIRST_PERSON) ? THIRD_PERSON : FIRST_PERSON;
//        if (key == '1') cameraMode = FIRST_PERSON;
//        if (key == '3') cameraMode = THIRD_PERSON;
//
//        // Движение (WASD)
//        float nX = posX, nZ = posZ;
//        if (key == 'w') { nX += sin(angle) * speed; nZ -= cos(angle) * speed; }
//        if (key == 's') { nX -= sin(angle) * speed; nZ += cos(angle) * speed; }
//        if (key == 'a') angle -= 0.1f;
//        if (key == 'd') angle += 0.1f;
//
//        // Проверка коллизий со стенами по каждой оси отдельно
//        if (maze[(int)(nX + 0.5f)][(int)(posZ + 0.5f)] == 0) posX = nX;
//        if (maze[(int)(posX + 0.5f)][(int)(nZ + 0.5f)] == 0) posZ = nZ;
//
//        glutPostRedisplay();
//    }
//}
//
//void reshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION); glLoadIdentity();
//    gluPerspective(60.0, (float)w / h, 0.1, 100.0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(1024, 768);
//    glutCreateWindow("3D Labyrinth - 1st / 3rd person");
//
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_TEXTURE_2D);
//
//    // Чтобы glColor влиял на цвет материала при включённом освещении
//    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
//
//    loadTexture("stena.jpg", wallTexture);
//    loadTexture("yellow.jpg", coinTexture);
//
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutKeyboardFunc(keyboard);
//    glutMouseFunc(mouse);
//    glutTimerFunc(0, timer, 0);
//
//    glutMainLoop();
//    return 0;
//}

#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

using namespace std;

const float PI = 3.14159265f;

// --- Состояние игры ---
enum GameState { MENU, PLAYING };
GameState currentState = MENU;

// --- Режим камеры: вид от 1-го или 3-го лица ---
enum CameraMode { FIRST_PERSON, THIRD_PERSON };
CameraMode cameraMode = FIRST_PERSON;

// --- Координаты кнопки меню ---
float btnLeft = -0.3f, btnRight = 0.3f;
float btnTop = 0.05f, btnBottom = -0.15f;

// --- Игрок ---
float posX = 1.5f, posZ = 1.5f, angle = 0.0f;
float playerRadius = 0.18f, speed = 0.12f;

// --- Монета (анимированная, с физикой) ---
float coinAngle = 0.0f;
float coinX = 1.0f, coinZ = 1.0f;   // позиция
float coinSpeed = 0.04f;            // скорость движения монеты
float coinDirZ = 1.0f;              // направление движения (1 или -1)
float coinRadius = 0.25f;           // радиус монеты (для коллизий)

// --- Лабиринт ---
const int MAZE_WIDTH = 10, MAZE_HEIGHT = 10;
int maze[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,0,1,1,1,0,1},
    {1,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

GLuint wallTexture, coinTexture;

void loadTexture(const char* filename, GLuint& id) {
    int w, h, c;
    unsigned char* data = stbi_load(filename, &w, &h, &c, 4);
    if (!data) { cout << "Не удалось загрузить: " << filename << endl; return; }
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

// --- Отрисовка вертикальной монетки и её тени ---
void drawVerticalCoin(float x, float z) {
    // 1. ТЕНЬ — лежит на полу
    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(x, 0.01f, z);
    glRotatef(90, 1, 0, 0);          // тень лежит горизонтально
    glScalef(1.0f, 2.0f, 0.1f);      // делаем плоской/вытянутой
    GLUquadric* qShadow = gluNewQuadric();
    gluDisk(qShadow, 0, 0.3, 30, 1);
    gluDeleteQuadric(qShadow);
    glPopMatrix();
    glDisable(GL_BLEND); glEnable(GL_LIGHTING); glEnable(GL_TEXTURE_2D); glColor3f(1, 1, 1);

    // 2. МОНЕТА (вертикальная, катится как колесо)
    glPushMatrix();
    glTranslatef(x, coinRadius, z);  // поднимаем центр, чтобы катилась по полу
    glRotatef(coinAngle, 0, 1, 0);   // вращение вокруг своей оси

    GLfloat mat_spec[] = { 1.0f, 1.0f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialf(GL_FRONT, GL_SHININESS, 128.0f);

    glBindTexture(GL_TEXTURE_2D, coinTexture);
    GLUquadric* qCoin = gluNewQuadric();
    gluQuadricTexture(qCoin, GL_TRUE);

    glTranslatef(0, 0, -0.025f);                 // центрируем толщину
    gluCylinder(qCoin, coinRadius, coinRadius, 0.05, 30, 1);
    gluDisk(qCoin, 0, coinRadius, 30, 1);        // задняя крышка
    glTranslatef(0, 0, 0.05f);
    gluDisk(qCoin, 0, coinRadius, 30, 1);        // передняя крышка

    gluDeleteQuadric(qCoin);
    glPopMatrix();
}

// --- Отрисовка персонажа (видна только в 3-м лице) с тенью ---
void drawPlayer() {
    // 1. ТЕНЬ персонажа
    glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(posX, 0.02f, posZ);
    glRotatef(90, 1, 0, 0);                      // тень лежит на полу
    GLUquadric* qSh = gluNewQuadric();
    gluDisk(qSh, 0, playerRadius * 1.3f, 30, 1);
    gluDeleteQuadric(qSh);
    glPopMatrix();
    glDisable(GL_BLEND); glEnable(GL_LIGHTING);

    // 2. ТЕЛО персонажа
    glPushMatrix();
    glTranslatef(posX, 0.0f, posZ);
    glRotatef(-angle * 180.0f / PI, 0, 1, 0);    // поворот в сторону взгляда

    // Туловище — цилиндр
    glColor3f(0.15f, 0.45f, 0.9f);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);                     // ставим цилиндр вертикально
    GLUquadric* qBody = gluNewQuadric();
    gluCylinder(qBody, playerRadius, playerRadius * 0.6f, 0.5f, 20, 1);
    gluDeleteQuadric(qBody);
    glPopMatrix();

    // Голова — сфера
    glColor3f(1.0f, 0.82f, 0.6f);
    glPushMatrix();
    glTranslatef(0.0f, 0.62f, 0.0f);
    glutSolidSphere(0.13f, 20, 20);
    glPopMatrix();

    // "Нос" — конус, показывает направление взгляда (-Z)
    glColor3f(0.9f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0.0f, 0.62f, -0.10f);
    glRotatef(180, 0, 1, 0);                     // разворачиваем конус на -Z
    glutSolidCone(0.05f, 0.15f, 12, 6);
    glPopMatrix();

    glPopMatrix();
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
}

void timer(int v) {
    // 1. Анимация вращения монеты
    coinAngle += 5.0f;
    if (coinAngle > 360) coinAngle -= 360;

    // 2. Физика движения монеты + коллизии со стенами
    float nextZ = coinZ + coinSpeed * coinDirZ;
    int checkGridZ = (int)(nextZ + (coinRadius * coinDirZ) + 0.5f);
    int currentGridX = (int)(coinX + 0.5f);

    if (checkGridZ >= 0 && checkGridZ < MAZE_HEIGHT) {
        if (maze[currentGridX][checkGridZ] == 0) {
            coinZ = nextZ;
        }
        else {
            coinDirZ *= -1.0f;
            coinZ += coinSpeed * coinDirZ;
        }
    }
    else {
        coinDirZ *= -1.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Экранные координаты -> координаты OpenGL (-1..1)
        float openGL_X = ((float)x / 1024.0f) * 2.0f - 1.0f;
        float openGL_Y = 1.0f - ((float)y / 768.0f) * 2.0f;

        // Проверка попадания клика в кнопку "Играть"
        if (currentState == MENU &&
            openGL_X > btnLeft && openGL_X < btnRight &&
            openGL_Y > btnBottom && openGL_Y < btnTop) {
            currentState = PLAYING;
            glutPostRedisplay();
        }
    }
}

// --- Вывод текста ---
void drawText(float x, float y, const char* str, void* font) {
    glRasterPos2f(x, y);
    for (int i = 0; str[i] != '\0'; i++)
        glutBitmapCharacter(font, str[i]);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (currentState == MENU) {
        // --- 2D-режим для меню ---
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);

        // Заголовок
        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(-0.32f, 0.45f, "3D LABYRINTH GAME", GLUT_BITMAP_TIMES_ROMAN_24);

        // Кнопка "Играть"
        glColor3f(0.2f, 0.2f, 0.8f);
        glBegin(GL_QUADS);
        glVertex2f(btnLeft, btnBottom);
        glVertex2f(btnRight, btnBottom);
        glVertex2f(btnRight, btnTop);
        glVertex2f(btnLeft, btnTop);
        glEnd();

        // Текст на кнопке
        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(-0.16f, -0.06f, "PLAY GAME", GLUT_BITMAP_HELVETICA_18);

        // Подсказка по управлению
        glColor3f(0.8f, 0.8f, 0.8f);
        drawText(-0.45f, -0.40f, "Mouse - click PLAY    WASD - move", GLUT_BITMAP_HELVETICA_12);
        drawText(-0.45f, -0.50f, "V - switch view (1st / 3rd person)", GLUT_BITMAP_HELVETICA_12);

        // Возврат настроек
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
    }
    else {
        // --- 3D-режим (игра) ---
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, 1024.0 / 768.0, 0.1, 100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // === КАМЕРА: вид от 1-го или 3-го лица ===
        if (cameraMode == FIRST_PERSON) {
            gluLookAt(posX, 0.5f, posZ,
                posX + sin(angle), 0.5f, posZ - cos(angle),
                0, 1, 0);
        }
        else { // THIRD_PERSON — камера позади и выше игрока
            float dist = 1.4f;
            // не даём камере провалиться сквозь стену
            while (dist > 0.3f) {
                float cx = posX - sin(angle) * dist;
                float cz = posZ + cos(angle) * dist;
                int gx = (int)(cx + 0.5f), gz = (int)(cz + 0.5f);
                if (gx >= 0 && gx < MAZE_WIDTH && gz >= 0 && gz < MAZE_HEIGHT
                    && maze[gx][gz] == 0)
                    break;
                dist -= 0.1f;
            }
            float camX = posX - sin(angle) * dist;
            float camZ = posZ + cos(angle) * dist;
            gluLookAt(camX, 1.1f, camZ,      // позиция камеры
                posX, 0.45f, posZ,     // смотрим на игрока
                0, 1, 0);
        }

        GLfloat lightPos[] = { posX, 0.8f, posZ, 1.0f };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

        // --- Отрисовка лабиринта ---
        glBindTexture(GL_TEXTURE_2D, wallTexture);
        for (int i = 0; i < MAZE_WIDTH; i++) {
            for (int j = 0; j < MAZE_HEIGHT; j++) {
                if (maze[i][j] == 1) {
                    float s = 0.5f;
                    glPushMatrix(); glTranslatef(i, 0.5f, j);
                    glBegin(GL_QUADS);
                    glNormal3f(0, 0, 1);  glTexCoord2f(0, 0); glVertex3f(-s, -s, s);  glTexCoord2f(1, 0); glVertex3f(s, -s, s);  glTexCoord2f(1, 1); glVertex3f(s, s, s);  glTexCoord2f(0, 1); glVertex3f(-s, s, s);
                    glNormal3f(0, 0, -1); glTexCoord2f(0, 0); glVertex3f(-s, -s, -s); glTexCoord2f(1, 0); glVertex3f(s, -s, -s); glTexCoord2f(1, 1); glVertex3f(s, s, -s); glTexCoord2f(0, 1); glVertex3f(-s, s, -s);
                    glNormal3f(1, 0, 0);  glTexCoord2f(0, 0); glVertex3f(s, -s, -s);  glTexCoord2f(1, 0); glVertex3f(s, s, -s);  glTexCoord2f(1, 1); glVertex3f(s, s, s);  glTexCoord2f(0, 1); glVertex3f(s, -s, s);
                    glNormal3f(-1, 0, 0); glTexCoord2f(0, 0); glVertex3f(-s, -s, -s); glTexCoord2f(1, 0); glVertex3f(-s, s, -s); glTexCoord2f(1, 1); glVertex3f(-s, s, s); glTexCoord2f(0, 1); glVertex3f(-s, -s, -s);
                    glEnd(); glPopMatrix();
                }
                else {
                    glDisable(GL_TEXTURE_2D); glColor3f(0.2f, 0.2f, 0.2f);
                    glBegin(GL_QUADS); glNormal3f(0, 1, 0);
                    glVertex3f(i - 0.5f, 0, j - 0.5f); glVertex3f(i + 0.5f, 0, j - 0.5f);
                    glVertex3f(i + 0.5f, 0, j + 0.5f); glVertex3f(i - 0.5f, 0, j + 0.5f);
                    glEnd();
                    glEnable(GL_TEXTURE_2D); glColor3f(1, 1, 1);
                }
            }
        }

        // Монета с тенью
        drawVerticalCoin(coinX, coinZ);

        // Персонаж рисуется только в виде от 3-го лица
        if (cameraMode == THIRD_PERSON)
            drawPlayer();
    }
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // ESC — выход

    if (currentState == MENU) {
        if (key == 13) { // ENTER — тоже запускает игру
            currentState = PLAYING;
            glutPostRedisplay();
        }
    }
    else if (currentState == PLAYING) {
        // Переключение вида камеры
        if (key == 'v' || key == 'V')
            cameraMode = (cameraMode == FIRST_PERSON) ? THIRD_PERSON : FIRST_PERSON;
        if (key == '1') cameraMode = FIRST_PERSON;
        if (key == '3') cameraMode = THIRD_PERSON;

        // Движение (WASD)
        float nX = posX, nZ = posZ;
        if (key == 'w') { nX += sin(angle) * speed; nZ -= cos(angle) * speed; }
        if (key == 's') { nX -= sin(angle) * speed; nZ += cos(angle) * speed; }
        if (key == 'a') angle -= 0.1f;
        if (key == 'd') angle += 0.1f;

        // Проверка коллизий со стенами по каждой оси отдельно
        if (maze[(int)(nX + 0.5f)][(int)(posZ + 0.5f)] == 0) posX = nX;
        if (maze[(int)(posX + 0.5f)][(int)(nZ + 0.5f)] == 0) posZ = nZ;

        glutPostRedisplay();
    }
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
    glutCreateWindow("3D Labyrinth - 1st / 3rd person");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);

    // Чтобы glColor влиял на цвет материала при включённом освещении
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    loadTexture("stena.jpg", wallTexture);
    loadTexture("yellow.jpg", coinTexture);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}


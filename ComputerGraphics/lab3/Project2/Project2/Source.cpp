#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>

using namespace std;

GLuint textures[10];
int currentTextureIndex = 0;
float angle = 0.0f;

// 1. Загрузка из файла (RGBA для стабильности)
GLuint loadTextureFromFile(const char* filename) {
    int w, h, chan;
    unsigned char* data = stbi_load(filename, &w, &h, &chan, 4);
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
        cout << "Loaded file: " << filename << endl;
    }
    else {
        cout << "Failed to load file: " << filename << ". Using fallback." << endl;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texID;
}

// 2. Генератор шахматной текстуры (как на фото 1)
GLuint createChessTexture() {
    const int size = 64;
    unsigned char data[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Математическое создание клеток
            int c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) ? 255 : 0;
            int idx = (i * size + j) * 3;
            data[idx] = data[idx + 1] = data[idx + 2] = (unsigned char)c;
        }
    }
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Исправляет ошибки выравнивания 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return texID;
}

// 3. Генератор радужной текстуры (как на фото 2)
GLuint createRainbowTexture() {
    const int size = 64;
    unsigned char data[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int idx = (i * size + j) * 3;
            data[idx] = (unsigned char)(i * 255 / size);         // R
            data[idx + 1] = (unsigned char)(j * 255 / size);     // G
            data[idx + 2] = (unsigned char)(255 - (i * 255 / size)); // B
        }
    }
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texID;
}

// 4. Генератор полосок (как на фото 3)
GLuint createStripedTexture() {
    const int size = 64;
    unsigned char data[size * size * 3];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int idx = (i * size + j) * 3;
            if ((j / 4) % 2 == 0) { // Полосы шириной в 4 пикселя
                data[idx] = 255; data[idx + 1] = 165; data[idx + 2] = 0; // Оранжевый
            }
            else {
                data[idx] = 0; data[idx + 1] = 100; data[idx + 2] = 255;   // Синий
            }
        }
    }
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return texID;
}

// Геометрия куба (8 вершин) [cite: 100-110]
static const GLfloat cubeVertices[] = {
    -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, // Перед
    -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f, // Зад
    -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f, // Верх
    -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, // Низ
     1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f, // Право
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f  // Лево
};

// Текстурные координаты [cite: 121-128]
static const GLfloat texCoords[] = {
    0.0f,0.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
    0.0f,0.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
    0.0f,0.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
    0.0f,0.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
    0.0f,0.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f,
    0.0f,0.0f, 1.0f,0.0f, 1.0f,1.0f, 0.0f,1.0f
};

void keyboard(unsigned char key, int x, int y) {
    if (key >= '1' && key <= '5') {
        currentTextureIndex = key - '1';
        cout << "Switching to texture #" << key << endl;
    }
    glutPostRedisplay();
}

void initializeGL() {
    glewInit();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Настройка взаимодействия (из методички пункт 6) [cite: 15]
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Загрузка
    textures[0] = loadTextureFromFile("texture.jpg");  // Твоя картинка (Клавиша 1)
    textures[1] = loadTextureFromFile("texture1.jpg"); // Твоя картинка (Клавиша 2)
    textures[2] = createChessTexture();               // Шахматка (Клавиша 3)
    textures[3] = createRainbowTexture();             // Радуга (Клавиша 4)
    textures[4] = createStripedTexture();             // Полоски (Клавиша 5)
}

void paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(angle, 1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, textures[currentTextureIndex]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void update(int v) {
    angle += 1.0f; // Исправлено (в методичке была опечатка )
    if (angle >= 360.0f) angle -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab 3");

    initializeGL();

    glutDisplayFunc(paintGL);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}